#include "BMP8PixelParser.hpp"

#include <stdexcept>

BMP8PixelParser::BMP8PixelParser(const BMP &bmp, const BMPPixelParser::MaskType mask)
    : BMPPixelParser{ bmp, mask }
{}

BMPPixelParser::ReadBMPPair BMP8PixelParser::ReadPixel(std::ifstream& reader) noexcept
{
    const std::streamsize bytesToRead = ((m_Pixels.empty()) ? (0x1) : (0x0));

    if (m_Pixels.empty())
    {
        BMPPixelParser::PixelType byte{};
        reader.read(reinterpret_cast<char*>(&byte), bytesToRead);

        FillPixelsQueue(byte); 
    }
    
    return { bytesToRead, GetLastPixel() }; 
}

// TODO: Get out of exceptions

void BMP8PixelParser::FillPixelsQueue(BMPPixelParser::PixelType byte) noexcept
{
    for (ImageFormat::ScreenResolution width = m_Image.Width; 
            width && byte; --width, byte >>= m_MaskBitsCount)
    {
        PixelType value = byte & m_Mask;

        m_Pixels.push(m_Image.ColorTable[value]);
    }
}

Pixel BMP8PixelParser::GetLastPixel() noexcept(false)
{ 
    if (m_Pixels.empty())
    {
        throw std::runtime_error{ "The queue of pixels is currently empty" }; 
    }

    Pixel pixel{ std::move(m_Pixels.back()) };
    m_Pixels.pop();

    return pixel;
}
