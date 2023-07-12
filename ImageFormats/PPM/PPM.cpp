#include "PPM.hpp"

PPM::PPM(PPM&& ppm)
    : ImageFormat{ std::move(ppm) }, m_Format{ std::move(ppm.m_Format) },
        m_PixelMaxValue{ ppm.m_PixelMaxValue }
{}   

PPM::PPM(const ImageFormat& image, const std::string& format, 
            const std::uint16_t pixelMaxValue) 
    : ImageFormat{ image }, m_Format{ format }, m_PixelMaxValue{ pixelMaxValue }  
{}

PPM::PPM(ImageFormat&& image, std::string&& format, 
        const std::uint16_t pixelMaxValue)
    : ImageFormat{ std::move(image) }, m_Format{ std::move(format) },
        m_PixelMaxValue{ pixelMaxValue }
{}

std::string& PPM::GetFormat() noexcept
{
    return m_Format; 
}

const std::string& PPM::GetFormat() const noexcept
{
    return const_cast<PPM*>(this)->GetFormat();
}

std::uint16_t& PPM::GetPixelMaxValue() noexcept
{
    return m_PixelMaxValue;
}

const std::uint16_t& PPM::GetPixelMaxValue() const noexcept
{
    return const_cast<PPM*>(this)->GetPixelMaxValue();
}
