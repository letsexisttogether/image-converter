#include "P6DataParser.hpp"
#include "Extra/PixelExtra.hpp"

P6DataParser::P6DataParser(std::ifstream& m_FileReader, const PPM& ppm)
    : PPMDataParser{ m_FileReader }, m_ColorSize(((ppm.PixelMaxValue > 255) ? 
            (sizeof(std::uint16_t)) : (sizeof(std::uint8_t)))) 
{}

Pixel P6DataParser::ReadPixel() noexcept
{
    Pixel pixel{};

    ReadAsBytes(m_FileReader, m_ColorSize, std::vector<Pixel::ColorValue*>
            {
                &pixel.Red,
                &pixel.Green,
                &pixel.Blue
            });

    return pixel;
}
