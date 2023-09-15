#pragma once

#include "ImageReaders/PPM/DataParsers/PPMDataParser.hpp"

class P3DataParser : public PPMDataParser
{
public:
    P3DataParser(std::ifstream& fileReader);

    ~P3DataParser() = default;

    Pixel ReadPixel() noexcept override; 
};
