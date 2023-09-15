#pragma once

#include "ImageWriters/PPM/DataCoders/PPMDataCoder.hpp"

class P3DataCoder : public PPMDataCoder
{
public:
    P3DataCoder(std::ofstream& fileWriter);

    ~P3DataCoder();
        
    void CodeData(const Pixel& pixel) noexcept override;
};
