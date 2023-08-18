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
    
    PPM(const ImageFormat& image);
    PPM(ImageFormat&& image);
    PPM(const ImageFormat& image, const std::string& format, 
            const std::uint16_t pixelMaxValue); 
    PPM(ImageFormat&& image, std::string&& format, 
            const std::uint16_t pixelMaxValue);

    ~PPM() = default;

    PPM& operator = (const PPM&) = default;
    PPM& operator = (PPM&& ppm);

public:
    std::string Format{};
    Pixel::ColorValue PixelMaxValue{};       
};
