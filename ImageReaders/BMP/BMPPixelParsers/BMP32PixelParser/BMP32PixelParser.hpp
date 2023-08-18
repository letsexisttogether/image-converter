#pragma once

#include "ImageReaders/BMP/BMPPixelParsers/BMPPixelParser.hpp"

class BMP32PixelParser: public BMPPixelParser
{
public:
    BMP32PixelParser(const BMP& bmp, const BMPPixelParser::MaskType mask, 
            const bool isAlpha);
    
    ~BMP32PixelParser() = default;

    ReadBMPPair ReadPixel(std::ifstream& reader) noexcept override;

private:
    Pixel MakePixelFromByteSet(PixelType byteSet);

private:
    const bool m_IsAlpha{};
};
