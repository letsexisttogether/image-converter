#pragma once

#include <cstdint>
#include <string>

#include "../ImageFormat.hpp"

class PPM : public ImageFormat 
{
public:
    PPM() = default;
    PPM(const PPM&) = default;
    PPM(PPM&& ppm);

    PPM(const ImageFormat& image, const std::string& format, 
            const std::uint16_t pixelMaxValue); 
    PPM(ImageFormat&& image, std::string&& format, 
            const std::uint16_t pixelMaxValue);

    ~PPM() = default;

    std::string& GetFormat() noexcept; 
    const std::string& GetFormat() const noexcept; 

    std::uint16_t& GetPixelMaxValue() noexcept;
    const std::uint16_t& GetPixelMaxValue() const noexcept;

    PPM& operator = (const PPM&) = default;
    PPM& operator = (PPM&& ppm);

private:
    std::string m_Format{};
	std::uint16_t m_PixelMaxValue{};       
};
