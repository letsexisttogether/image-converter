#include "BMPReader.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "ImageFormats/ImageFormat.hpp"
#include "DataParsers/BMP8/BMP8DataParser.hpp"
#include "DataParsers/BMP32/BMP32DataParser.hpp"

BMPReader::BMPReader(std::ifstream&& reader, Fabric&& parsersFabric) 
    : ImageReaderRealization<BMP>{ std::forward<std::ifstream>(reader) },
        m_Fabric(std::move(parsersFabric))
{}

void BMPReader::ReadHeader() noexcept
{
    auto readField = [this](auto& field)
    {
        m_FileReader.read(reinterpret_cast<char*>(&field), sizeof(field));
    };

    readField(m_Image.HeaderField[0]);
    readField(m_Image.HeaderField[1]);
    readField(m_Image.FileSize);
    readField(m_Image.Reserved[0]);
    readField(m_Image.Reserved[1]);
    readField(m_Image.DataOffset);

    m_FileReader.seekg(0xE, std::ios::beg);

    readField(m_Image.InfoHeaderSize);
    readField(m_Image.Width);
    readField(m_Image.Height);
    readField(m_Image.ColorPlanesNumber);
    readField(m_Image.BitsPerPixel);
    readField(m_Image.CompressionMethod);
    readField(m_Image.ImageSize);
    readField(m_Image.HorizontalResolution);
    readField(m_Image.VertivalResolution);
    readField(m_Image.ColorPaletteNumber);
    readField(m_Image.ImportantColorsNumber);
}

void BMPReader::ReadData() noexcept 
{
    ReadColorTable();

    m_FileReader.seekg(m_Image.DataOffset, std::ios::beg);

    std::unique_ptr<BMPDataParser> bmpParser
    {
        m_Fabric.SpawnObject(m_Image.BitsPerPixel, m_FileReader, m_Image)
    };

    const auto& [height, width] = m_Image.GetResolution();

    m_Image.Data.resize(height);

    for (ImageFormat::ScreenResolution h = height - 1; h >= 0; --h)
    {
        ImageFormat::DataRow row{};

        BMPDataParser::ReadSize bitsRead = 0;

        for (ImageFormat::ScreenResolution w = 0; w < width; ++w)
        {
            const auto& [readSize, pixel] = bmpParser->ReadPixel();

            bitsRead += readSize;
              
            row.push_back(pixel);
        }

        RemovePadding(bitsRead);

        m_Image.Data[h] = std::move(row);
    } 
}

void BMPReader::CheckHeader() const noexcept(false)
{
    if (const auto& headerField = m_Image.HeaderField; 
            headerField[0] != 'B' || headerField[1] != 'M')
    {
        throw std::runtime_error { "The BMP file signature was not found: BM needed" };
    }

    if (!(m_Image.Height * m_Image.Width))
    {
        throw std::runtime_error{ "Resolution cannot be 0" };
    }
}

void BMPReader::CheckData() const noexcept(false)
{}

void BMPReader::ReadColorTable() noexcept
{
    for (std::uint32_t i = 0; i < m_Image.ColorPaletteNumber; ++i)
    {
        Pixel color{};

        ReadAsBytes(m_FileReader, sizeof(std::uint8_t),
                    std::vector<Pixel::ColorValue*>
                    {
                        &color.Blue, &color.Green, &color.Red, &color.Alpha 
                    });
        color.Alpha = Pixel::DefaultAlpha; 
        

        m_Image.ColorTable.push_back(std::move(color));
    }
}

void BMPReader::RemovePadding(const std::int32_t bytesRead) noexcept 
{
    const std::int32_t paddingAllignment = 0x4;
    const std::streamsize bytesLeft = paddingAllignment - (bytesRead % paddingAllignment);
    
    if (bytesLeft != paddingAllignment)
    {
        char buffer[bytesLeft];
        m_FileReader.read(buffer, bytesLeft);
    }
}

// DLL 
extern "C" __declspec(dllexport) ImageReader* CreateReader
    (std::ifstream&& reader)
{
    // Yes, we hardcode
    BMPReader::Fabric fabric
    {
        BMPReader::Fabric::FunctionsMap
        {
            { 
                0x1, [](std::ifstream& reader, const BMP& bmp) -> BMPDataParser* 
                { return new BMP8DataParser(reader, bmp, 0b1); } 
            },
            { 
                0x2, [](std::ifstream& reader, const BMP& bmp) -> BMPDataParser* 
                { return new BMP8DataParser(reader, bmp, 0b11); } 
            },
            { 
                0x4, [](std::ifstream& reader, const BMP& bmp) -> BMPDataParser* 
                { return new BMP8DataParser(reader, bmp, 0b1111); } 
            },
            {
                0x8, [](std::ifstream& reader, const BMP& bmp) -> BMPDataParser* 
                { return new BMP8DataParser(reader, bmp, 0x11111111); } 
            },
            { 
                0x10, [](std::ifstream& reader, const BMP& bmp) -> BMPDataParser* 
                { return new BMP32DataParser(reader, bmp, 0x1111, true); } 
            },
            { 
                0x18, [](std::ifstream& reader, const BMP& bmp) -> BMPDataParser* 
                { return new BMP32DataParser(reader, bmp, 0b11111111, false); } 
            },
            { 
                0x20, [](std::ifstream& reader, const BMP& bmp) -> BMPDataParser* 
                { return new BMP32DataParser(reader, bmp, 0b11111111, true); } 
            }
        }
    };

    return new BMPReader{ std::forward<std::ifstream>(reader), 
        std::move(fabric) };
}
