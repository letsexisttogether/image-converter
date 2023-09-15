#pragma once

#include "ImageWriters/PPM/DataCoders/PPMDataCoder.hpp"
#include "ImageFormats/PPM/PPM.hpp"

class P6DataCoder : public PPMDataCoder
{
public:
    P6DataCoder(std::ofstream& fileWriter, const PPM& ppm);

    ~P6DataCoder() = default;
        
    void CodeData(const Pixel& pixel) noexcept override;

private:
    const std::streamsize m_ColorSize;
};
