#include "BMP32DataParser.hpp"

BMP32DataParser::BMP32DataParser(std::ifstream& fileReader, const BMP &bmp, 
        const BMPDataParser::MaskType mask, const bool isAlpha)
    : BMPDataParser{ fileReader, bmp, mask }, m_IsAlpha{ isAlpha }
{}

BMPDataParser::ReadBMPPair BMP32DataParser::ReadPixel() noexcept
{
    const std::streamsize bytesToRead = m_Image.BitsPerPixel / 0x8;
    
    BMPDataParser::PixelType byteSet{};
    
    m_FileReader.read(reinterpret_cast<char*>(&byteSet), bytesToRead);

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
