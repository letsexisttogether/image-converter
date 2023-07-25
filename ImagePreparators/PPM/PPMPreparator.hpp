#pragma once

#include "../ImagePreparator.hpp"
#include "ImageFormats/PPM/PPM.hpp"

class PPMPreparator : public ImagePreparator
{
public:
    PPMPreparator(PPM& image);

    ~PPMPreparator() = default;

    void PrepareImage() noexcept override;

protected:
    virtual std::string GetFormat() const noexcept; 

private:
    Pixel::Byte GetPixelMaxValue() const noexcept; 

private: 
    PPM& m_Image;
};
