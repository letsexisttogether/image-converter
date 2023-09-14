#pragma once

#include <fstream>

#include "Pixel/Pixel.hpp"

class PPMDataParser
{
public:
    PPMDataParser() = default;

    virtual ~PPMDataParser() = default;

    virtual Pixel ReadPixel(std::ifstream& fileReader) noexcept = 0; 
};
