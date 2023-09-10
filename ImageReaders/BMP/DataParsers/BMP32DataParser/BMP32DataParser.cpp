#include "BMP32DataParser.hpp"

BMP32DataParser::BMP32DataParser(const BMP &bmp, const BMPDataParser::MaskType mask, 
            const bool isAlpha)
    : BMPDataParser{ bmp, mask }, m_IsAlpha{ isAlpha }
{}

BMPDataParser::ReadBMPPair BMP32DataParser::ReadPixel(std::ifstream& reader) noexcept
{
    const std::streamsize bytesToRead = m_Image.BitsPerPixel / 0x8;
    
    BMPDataParser::PixelType byteSet{};
    
    reader.read(reinterpret_cast<char*>(&byteSet), bytesToRead);

    return { bytesToRead, MakePixelFromByteSet(byteSet) }; 
}

Pixel BMP32DataParser::MakePixelFromByteSet(PixelType byteSet)
{
    auto makeColorValue = [&] (Pixel::ColorValue& value)
    {
        value = byteSet & m_Mask;

        byteSet >>= m_MaskBitsCount;
    };

    Pixel pixel{};

    makeColorValue(pixel.Blue);
    makeColorValue(pixel.Green);
    makeColorValue(pixel.Red);

    if (m_IsAlpha)
    {
        makeColorValue(pixel.Alpha);
    }

    return pixel;
}
