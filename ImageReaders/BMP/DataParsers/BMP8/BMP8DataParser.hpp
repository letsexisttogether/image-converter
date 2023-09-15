#pragma once

#include <queue>

#include "ImageReaders/BMP/DataParsers/BMPDataParser.hpp"

class BMP8DataParser: public BMPDataParser
{
public:
    BMP8DataParser(std::ifstream& fileReader, const BMP& bmp, const BMPDataParser::MaskType mask);
    
    ~BMP8DataParser() = default;

    ReadBMPPair ReadPixel() noexcept override;

private:
    void FillPixelsQueue(PixelType byte) noexcept;

    Pixel GetLastPixel() noexcept(false);

private:
    std::queue<Pixel> m_Pixels{};
};
