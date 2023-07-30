#include "PPMPreparator.hpp"

PPMPreparator::PPMPreparator(PPM& image) 
    : m_Image{ image }
{}

void PPMPreparator::PrepareImage() noexcept
{
    m_Image.Format = GetFormat(); 
    m_Image.PixelMaxValue = GetPixelMaxValue();
}

Pixel::Byte PPMPreparator::GetPixelMaxValue() const noexcept
{
    Pixel::Byte maxValue{};

    auto findMax = [&maxValue](const Pixel::Byte& value)
    {
        maxValue = std::max(maxValue, value);
    };

    for (const auto& row : m_Image.Data)
    {
        for (const Pixel& pixel : row)
        {
            const auto& [r, g, b] = pixel.GetColorValues();

            findMax(r);
            findMax(g);
            findMax(b);
        }
    }

    return maxValue;
};

std::string PPMPreparator::GetFormat() const noexcept
{
    return "P3";
}
