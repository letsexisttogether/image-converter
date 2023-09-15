#pragma once

#include "ImageReaders/BMP/DataParsers/BMPDataParser.hpp"

class BMP32DataParser: public BMPDataParser
{
public:
    BMP32DataParser(std::ifstream& fileReader, const BMP& bmp, 
            const BMPDataParser::MaskType mask, const bool isAlpha);
    
    ~BMP32DataParser() = default;

    ReadBMPPair ReadPixel() noexcept override;

private:
    Pixel MakePixelFromByteSet(PixelType byteSet);

private:
    const bool m_IsAlpha{};
};
