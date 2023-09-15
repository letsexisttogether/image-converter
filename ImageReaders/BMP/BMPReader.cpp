#include "BMPReader.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "ImageFormats/ImageFormat.hpp"

BMPReader::BMPReader(std::ifstream&& reader, Fabric&& parsersFabric) 
    : ImageReaderRealization<BMP>{ std::forward<std::ifstream>(reader) },
        m_Fabric(std::move(parsersFabric))
{}

void BMPReader::ReadHeader() noexcept
{
    auto readAndPrintField = [this](auto& field, const std::string& fieldName) 
    {
        m_FileReader.read(reinterpret_cast<char*>(&field), sizeof(field));
        std::cout << fieldName << " : " << field << std::endl;
    };

    readAndPrintField(m_Image.HeaderField[0], "HeaderField[0]");
    readAndPrintField(m_Image.HeaderField[1], "HeaderField[1]");
    readAndPrintField(m_Image.FileSize, "FileSize");
    readAndPrintField(m_Image.Reserved[0], "Reserved[0]");
    readAndPrintField(m_Image.Reserved[1], "Reserved[1]");
    readAndPrintField(m_Image.DataOffset, "DataOffset");

    m_FileReader.seekg(0xE, std::ios::beg);

    readAndPrintField(m_Image.InfoHeaderSize, "InfoHeaderSize");
    readAndPrintField(m_Image.Width, "Width");
    readAndPrintField(m_Image.Height, "Height");
    readAndPrintField(m_Image.ColorPlanesNumber, "ColorPlanesNumber");
    readAndPrintField(m_Image.BitsPerPixel, "BitsPerPixel");
    readAndPrintField(m_Image.CompressionMethod, "CompressionMethod");
    readAndPrintField(m_Image.ImageSize, "ImageSize");
    readAndPrintField(m_Image.HorizontalResolution, "HorizontalResolution");
    readAndPrintField(m_Image.VertivalResolution, "VertivalResolution");
    readAndPrintField(m_Image.ColorPaletteNumber, "ColorPaletteNumber");
    readAndPrintField(m_Image.ImportantColorsNumber, "ImportantColorsNumber");
}

void BMPReader::ReadData() noexcept 
{
    ReadColorTable();

    m_FileReader.seekg(m_Image.DataOffset, std::ios::beg);

    std::unique_ptr<BMPDataParser> bmpParser
    {
        m_Fabric.GetParser(m_Image.BitsPerPixel, m_FileReader, m_Image)
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
