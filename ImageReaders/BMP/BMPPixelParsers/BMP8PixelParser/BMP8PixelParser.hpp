#pragma once

#include <queue>

#include "ImageReaders/BMP/BMPPixelParsers/BMPPixelParser.hpp"

class BMP8PixelParser: public BMPPixelParser
{
public:
    BMP8PixelParser(const BMP& bmp, const BMPPixelParser::MaskType mask);
    
    ~BMP8PixelParser() = default;

    ReadBMPPair ReadPixel(std::ifstream& reader) noexcept override;

private:
    void MakePixelsFromByte(PixelType byte) noexcept;

    Pixel GetLastPixel() noexcept(false);

private:
    std::queue<Pixel> m_Pixels{};
};
