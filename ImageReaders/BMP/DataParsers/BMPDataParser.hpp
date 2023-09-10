#pragma once

#include <utility>

#include "ImageFormats/BMP/BMP.hpp"
#include "Extra/PixelExtra.hpp"

class BMPDataParser
{
public:
    using ReadSize = std::uint32_t;
    using ReadBMPPair = std::pair<ReadSize, Pixel>;
    using PixelType = std::uint32_t;
    using MaskType = PixelType;
public:
    BMPDataParser(const BMP& bmp, const MaskType mask) 
        : m_Image{ bmp }, m_Mask{ mask }, 
            m_MaskBitsCount{ CalculateSetBits(m_Mask) }
    {}

    virtual ~BMPDataParser() = default;
    
    virtual ReadBMPPair ReadPixel(std::ifstream& reader) noexcept = 0;

protected:
    const BMP& m_Image;
    const MaskType m_Mask{};
    const std::uint8_t m_MaskBitsCount{};
};
