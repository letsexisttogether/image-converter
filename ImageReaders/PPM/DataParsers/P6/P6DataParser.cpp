#include "P6DataParser.hpp"
#include "Extra/PixelExtra.hpp"

P6DataParser::P6DataParser(const PPM& ppm)
    : m_IsTwoBytes{ ppm.PixelMaxValue > 255 }
{}

Pixel P6DataParser::ReadPixel(std::ifstream& fileReader) noexcept
{
    const std::streamsize colorSize = ((m_IsTwoBytes) ? 
            (sizeof(std::uint16_t)) : (sizeof(std::uint8_t)));

    Pixel pixel{};

    ReadAsBytes(fileReader, colorSize, std::vector<Pixel::ColorValue*>
            {
                &pixel.Red,
                &pixel.Green,
                &pixel.Blue
            });

    return pixel;
}
