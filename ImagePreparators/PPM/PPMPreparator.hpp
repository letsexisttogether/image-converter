#pragma once

#include "../ImagePreparator.hpp"
#include "ImageFormats/PPM/PPM.hpp"

class PPMPreparator : public ImagePreparator
{
public:
    PPMPreparator(PPM& image);

    ~PPMPreparator() = default;

    void PrepareImage() noexcept override;

private:
    std::string GetFormat() const noexcept; 
    Pixel::Byte GetPixelMaxValue() const noexcept; 

private: 
    PPM& m_Image;
};
