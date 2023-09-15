#include "P6DataCoder.hpp"

P6DataCoder::P6DataCoder(std::ofstream& fileWriter, const PPM& ppm)
    : PPMDataCoder{ fileWriter }, m_ColorSize(((ppm.PixelMaxValue > 255) ? 
            (sizeof(std::uint16_t)) : (sizeof(std::uint8_t))))
{}

void P6DataCoder::CodeData(const Pixel& pixel) noexcept
{
    auto writeColor = [this] (const Pixel::ColorValue* color)
    {
        m_FileWriter.write(reinterpret_cast<const char*>(color), m_ColorSize);
    };

    writeColor(&pixel.Red);
    writeColor(&pixel.Green);
    writeColor(&pixel.Blue);
}
