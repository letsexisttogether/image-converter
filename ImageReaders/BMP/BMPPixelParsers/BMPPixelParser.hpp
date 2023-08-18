#pragma once

#include "ImageFormats/BMP/BMP.hpp"

class BMPPixelParser
{
public:
    using PixelType = std::uint32_t;

public:
    BMPPixelParser(const BMP& bmp) 
        : m_Image{ bmp } 
    {}

    virtual ~BMPPixelParser() = default;
    
    virtual std::uint32_t ReadPixel(std::ifstream& reader) noexcept = 0;

    virtual Pixel GetLastPixel() noexcept = 0; 

protected:
    const BMP& m_Image;
};
