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

    ~PPM() = default;

    PPM& operator = (const PPM&) = default;
    PPM& operator = (PPM&& ppm) = default;

public:
    std::string Format{};
    Pixel::ColorValue PixelMaxValue{};       
};
