#include "BMP8DataRowReader.hpp"

#include "Extra/PixelExtra.hpp"

BMP8DataRowReader::BMP8DataRowReader(std::ifstream& fileReader, BMP& bmp, 
        const std::uint8_t xorMask)
    : BMPDataRowReader{ fileReader, bmp }, m_XORMask{ xorMask }
{}

void BMP8DataRowReader::ReadNextRow() noexcept
{
    const std::uint8_t shift = CalculateSetBits(m_XORMask);

    ImageFormat::ScreenResolution pixelsLeft = m_BMP.Width * shift;
     
    ImageFormat::DataRow row{};

    for (std::uint8_t i = 0, bytesInBMPRow = sizeof(std::uint32_t); i < bytesInBMPRow; ++i)
    {
        std::uint8_t byte{};

        m_FileReader >> byte;

        byte = ReverseBits(byte);

        for (std::uint8_t mask = m_XORMask; pixelsLeft && mask; 
                pixelsLeft -= shift, mask >>= shift)
        {
            std::uint8_t index = byte & mask; 
            
            row.push_back(m_ColorTable[index]);
        }
    }

    m_BMP.Data.push_back(std::move(row));
}

void BMP8DataRowReader::ReadColorTable() noexcept
{
    for (std::uint32_t i = 0; i < m_BMP.ColorPaletteNumber; ++i)
    {
        Pixel color{};

        ReadAsBytes(m_FileReader, sizeof(std::uint8_t),
                    std::vector<Pixel::ColorValue*>
                    {
                        &color.Blue, &color.Green, &color.Red, &color.Alpha 
                    });
        color.Alpha = Pixel::DefaultAlpha; 
        

        m_ColorTable.push_back(std::move(color));
    }
};
