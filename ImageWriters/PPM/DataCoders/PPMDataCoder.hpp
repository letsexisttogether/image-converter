#pragma once

#include <ostream>

#include "Pixel/Pixel.hpp"

class PPMDataCoder
{
public:
    PPMDataCoder(std::ofstream& fileWriter)
        : m_FileWriter{ fileWriter }
    {}

    virtual ~PPMDataCoder() = default;
        
    virtual void CodeData(const Pixel& pixel) noexcept = 0;

protected:
    std::ofstream& m_FileWriter;
};
