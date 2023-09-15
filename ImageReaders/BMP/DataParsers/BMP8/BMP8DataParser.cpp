#include "BMP8DataParser.hpp"

#include <stdexcept>

BMP8DataParser::BMP8DataParser(std::ifstream& fileReader, 
        const BMP &bmp, const BMPDataParser::MaskType mask)
    : BMPDataParser{ fileReader, bmp, mask }
{}

BMPDataParser::ReadBMPPair BMP8DataParser::ReadPixel() noexcept
{
    const std::streamsize bytesToRead = ((m_Pixels.empty()) ? (0x1) : (0x0));

    if (m_Pixels.empty())
    {
        BMPDataParser::PixelType byte{};
        m_FileReader.read(reinterpret_cast<char*>(&byte), bytesToRead);

        FillPixelsQueue(byte); 
    }
    
    return { bytesToRead, GetLastPixel() }; 
}

// TODO: Get out of exceptions

void BMP8DataParser::FillPixelsQueue(BMPDataParser::PixelType byte) noexcept
{
    for (ImageFormat::ScreenResolution width = m_Image.Width; 
            width && byte; --width, byte >>= m_MaskBitsCount)
    {
        PixelType value = byte & m_Mask;

        m_Pixels.push(m_Image.ColorTable[value]);
    }
}

Pixel BMP8DataParser::GetLastPixel() noexcept(false)
{ 
    if (m_Pixels.empty())
    {
        throw std::runtime_error{ "The queue of pixels is currently empty" }; 
    }

    Pixel pixel{ std::move(m_Pixels.back()) };
    m_Pixels.pop();

    return pixel;
}
