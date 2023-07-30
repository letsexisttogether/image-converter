#include "PPM.hpp"

PPM::PPM(PPM&& ppm)
    : ImageFormat{ std::move(ppm) }, Format{ std::move(ppm.Format) },
        PixelMaxValue{ ppm.PixelMaxValue }
{}   

PPM::PPM(const ImageFormat& image)
    : ImageFormat{ image }
{}

PPM::PPM(ImageFormat&& image)
    : ImageFormat{ std::move(image) }
{}

PPM::PPM(const ImageFormat& image, const std::string& format, 
            const std::uint16_t pixelMaxValue) 
    : ImageFormat{ image }, Format{ format }, PixelMaxValue{ pixelMaxValue }  
{}

PPM::PPM(ImageFormat&& image, std::string&& format, 
        const std::uint16_t pixelMaxValue)
    : ImageFormat{ std::move(image) }, Format{ std::move(format) },
        PixelMaxValue{ pixelMaxValue }
{}

// Get info about operator = with rvalues for inheritated classes
PPM& PPM::operator = (PPM&& ppm)
{
    return *this;
}
