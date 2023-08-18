#include "BMPReader.hpp"

#include <ios>
#include <memory>

#include "BMPPixelParsers/BMP32PixelParser/BMP32PixelParser.hpp"

BMPReader::BMPReader(std::ifstream&& reader) 
    : ImageReaderRealization<BMP>{ std::forward<std::ifstream>(reader) }
{}

void BMPReader::ReadHeader() noexcept
{
    m_FileReader >> m_Image.HeaderField >> m_Image.FileSize >> m_Image.Reserved[0] 
        >> m_Image.Reserved[1] >> m_Image.DataOffset;

    m_FileReader >> m_Image.InfoHeaderSize >> m_Image.Width >> m_Image.Height 
        >> m_Image.ColorPlanesNumber >> m_Image.BitsPerPixel 
        >> m_Image.CompressionMethod >> m_Image.ImageSize 
        >> m_Image.HorizontalResolution >> m_Image.VertivalResolution 
        >> m_Image.ColorPaletteNumber >> m_Image.ImportantColorsNumber;
}

void BMPReader::ReadData() noexcept 
{
    std::unique_ptr<BMPPixelParser> bmpParser
    {
        new BMP32PixelParser{ m_Image, 0x20, true } 
    };

    for (ImageFormat::ScreenResolution h = 0; h < m_Image.Height; ++h)
    {
        ImageFormat::DataRow row{};

        BMPPixelParser::ReadSize bitsRead = 0;
        for (ImageFormat::ScreenResolution w = 0; w < m_Image.Width; ++w)
        {
            const auto& [readSize, pixel] = bmpParser->ReadPixel(m_FileReader);

            bitsRead += readSize;

            row.push_back(pixel);
        }

        RemovePadding(bitsRead);

        m_Image.Data.push_back(std::move(row));
    } 

}

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
    const std::streamsize bytesLeft = std::abs(bytesRead - paddingAllignment);

    char buffer[bytesLeft];
    m_FileReader.read(buffer, bytesLeft);
}

void BMPReader::CheckHeader() const noexcept(false)
{}

void BMPReader::CheckData() const noexcept(false)
{}