#pragma once

#include <cstdint>
#include <string>

#include "../ImageFormat.hpp"

class PPM : public ImageFormat 
{

public:
    PPM() = default;
    PPM(const PPM&) = default;
    PPM(PPM&& ppm) = default;

    PPM(const ImageFormat& image)
        : ImageFormat{ image } 
    {}
   
    PPM(ImageFormat&& image)
        : ImageFormat{ std::move(image) }
    {}

    ~PPM() = default;

    PPM& operator = (const PPM&) = default;
    PPM& operator = (PPM&& ppm) = default;

public:
    std::string Format{};
    Pixel::ColorValue PixelMaxValue{};       
};
