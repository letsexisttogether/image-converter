#include "BMP32PixelParser.hpp"
#include <iostream>

BMP32PixelParser::BMP32PixelParser(const BMP &bmp, const BMPPixelParser::MaskType mask, 
            const bool isAlpha)
    : BMPPixelParser{ bmp, mask }, m_IsAlpha{ isAlpha }
{}

BMPPixelParser::ReadBMPPair BMP32PixelParser::ReadPixel(std::ifstream& reader) noexcept
{
    const std::streamsize bytesToRead = m_Image.BitsPerPixel / 0x8;
    
    BMPPixelParser::PixelType byteSet{};
    
    reader.read(reinterpret_cast<char*>(&byteSet), bytesToRead);

    return { bytesToRead, MakePixelFromByteSet(byteSet) }; 
}

Pixel BMP32PixelParser::MakePixelFromByteSet(PixelType byteSet)
{
    auto makeColorValue = [&] (Pixel::ColorValue& value)
    {
        value = byteSet & m_Mask;

        byteSet >>= m_MaskBitsCount;
    };

    Pixel pixel{};

    if (m_IsAlpha)
    {
        makeColorValue(pixel.Alpha);
    }

    makeColorValue(pixel.Blue);
    makeColorValue(pixel.Green);
    makeColorValue(pixel.Red);

    return pixel;
}
