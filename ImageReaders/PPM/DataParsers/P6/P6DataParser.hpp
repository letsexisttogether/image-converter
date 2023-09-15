#pragma once 

#include "ImageReaders/PPM/DataParsers/PPMDataParser.hpp"
#include "ImageFormats/PPM/PPM.hpp"

class P6DataParser : public PPMDataParser
{
public:
    P6DataParser(std::ifstream& fileReader, const PPM& ppm);

    ~P6DataParser() = default;

    Pixel ReadPixel() noexcept override; 

private:
    const std::streamsize m_ColorSize;
};
