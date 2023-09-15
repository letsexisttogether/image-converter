#pragma once

#include <fstream>

#include "Pixel/Pixel.hpp"

class PPMDataParser
{
public:
    PPMDataParser(std::ifstream& fileReader)
        : m_FileReader{ fileReader }
    {}

    virtual ~PPMDataParser() = default;

    virtual Pixel ReadPixel() noexcept = 0; 

protected:
    std::ifstream& m_FileReader;
};
