#include "BMPDataRowReader.hpp"

BMPDataRowReader::BMPDataRowReader(std::ifstream& fileStream, BMP& bmp)
    : m_FileReader{ fileStream }, m_BMP{ bmp }
{}

void BMPDataRowReader::ReadColorTable() noexcept
{
    auto readColorValue = [&] (Pixel::ColorValue& value)
    {
        m_FileReader.read(reinterpret_cast<char*>(&value), sizeof(std::uint8_t));
    };

    for (std::uint32_t i = 0; i < m_BMP.ColorPaletteNumber; ++i)
    {
        Pixel color{};
        
        readColorValue(color.Blue);
        readColorValue(color.Green);
        readColorValue(color.Red);
        readColorValue(color.Alpha);

        m_ColorTable.push_back(std::move(color));
    }
};
