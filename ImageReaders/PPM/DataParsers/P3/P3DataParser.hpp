#pragma once

#include "ImageReaders/PPM/DataParsers/PPMDataParser.hpp"

class P3DataParser : public PPMDataParser
{
public:
    P3DataParser() = default;

    ~P3DataParser() = default;

    Pixel ReadPixel(std::ifstream& fileReader) noexcept override; 
};
