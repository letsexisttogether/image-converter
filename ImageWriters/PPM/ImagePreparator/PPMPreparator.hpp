#pragma once

#include "ImageWriters/ImagePreparator.hpp"
#include "ImageFormats/PPM/PPM.hpp"

class PPMPreparator : public ImagePreparator<PPM>
{
public:
    PPMPreparator(ImageFormat&& image);

    ~PPMPreparator() = default;

    PPM&& PrepareImage() noexcept override;

private:
    std::string GetFormat() const noexcept; 
    Pixel::ColorValue GetPixelMaxValue() const noexcept; 
};
