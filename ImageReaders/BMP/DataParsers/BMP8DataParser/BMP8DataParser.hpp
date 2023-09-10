#pragma once

#include <queue>

#include "ImageReaders/BMP/DataParsers/BMPDataParser.hpp"

class BMP8DataParser: public BMPDataParser
{
public:
    BMP8DataParser(const BMP& bmp, const BMPDataParser::MaskType mask);
    
    ~BMP8DataParser() = default;

    ReadBMPPair ReadPixel(std::ifstream& reader) noexcept override;

private:
    void FillPixelsQueue(PixelType byte) noexcept;

    Pixel GetLastPixel() noexcept(false);

private:
    std::queue<Pixel> m_Pixels{};
};
