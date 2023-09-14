#pragma once 

#include "ImageReaders/PPM/DataParsers/PPMDataParser.hpp"
#include "ImageFormats/PPM/PPM.hpp"

class P6DataParser : public PPMDataParser
{
public:
    P6DataParser(const PPM& ppm);

    ~P6DataParser() = default;

    Pixel ReadPixel(std::ifstream& fileReader) noexcept override; 

private:
    const bool m_IsTwoBytes{};
};
