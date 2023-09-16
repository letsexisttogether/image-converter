#include "PPMPreparator.hpp"

#include <utility>

PPMPreparator::PPMPreparator(ImageFormat&& image) 
    : ImagePreparator<PPM>(std::forward<ImageFormat>(image))
{}

PPM&& PPMPreparator::PrepareImage() noexcept
{
    m_Image.Format = GetFormat(); 
    m_Image.PixelMaxValue = GetPixelMaxValue();

    return std::move(m_Image);
}

Pixel::ColorValue PPMPreparator::GetPixelMaxValue() const noexcept
{
    Pixel::ColorValue maxValue{};

    auto findMax = [&maxValue](const Pixel::ColorValue& value)
    {
        maxValue = std::max(maxValue, value);
    };

    for (const auto& row : m_Image.Data)
    {
        for (const auto& [r, g, b, _] : row)
        {
            findMax(r);
            findMax(g);
            findMax(b);
        }
    }

    return maxValue;
};

std::string PPMPreparator::GetFormat() const noexcept
{
    // Yes, we hardcode
    return "P3";
}
