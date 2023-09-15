#pragma once

#include <fstream>
#include <utility>

#include "ImageFormats/BMP/BMP.hpp"
#include "Extra/PixelExtra.hpp"

class BMPDataParser
{
public:
    using ReadSize = std::int32_t;
    using ReadBMPPair = std::pair<ReadSize, Pixel>;
    using PixelType = std::uint32_t;
    using MaskType = PixelType;
public:
    BMPDataParser(std::ifstream& fileReader, const BMP& bmp, const MaskType mask) 
        : m_FileReader{ fileReader }, m_Image{ bmp }, 
            m_Mask{ mask }, m_MaskBitsCount{ CalculateSetBits(m_Mask) }
    {}

    virtual ~BMPDataParser() = default;
    
    virtual ReadBMPPair ReadPixel() noexcept = 0;

protected:
    const BMP& m_Image;
    std::ifstream& m_FileReader;
    const MaskType m_Mask{};
    const std::uint8_t m_MaskBitsCount{};
};
