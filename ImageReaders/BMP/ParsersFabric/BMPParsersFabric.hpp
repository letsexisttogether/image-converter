#pragma once

#include <map>

#include "ImageReaders/BMP/BMPPixelParsers/BMPPixelParser.hpp"

class BMPParsersFabric
{
public:
    using ConstructingFunc = BMPPixelParser* (*) (const BMP& bmp);
    using FunctionsMap = std::map<std::uint16_t, ConstructingFunc>;

public:
    BMPParsersFabric() = delete;
    BMPParsersFabric(const BMPParsersFabric&) = default;
    BMPParsersFabric(BMPParsersFabric&&) = default;

    BMPParsersFabric(const FunctionsMap& map);
    BMPParsersFabric(FunctionsMap&& map);

    ~BMPParsersFabric() = default;
    
    BMPPixelParser* GetBMPParser(const BMP& bmp) noexcept(false);

    bool CheckBPPExistance(const BMP::BPPType bpp) const noexcept;

    BMPParsersFabric& operator = (const BMPParsersFabric&) = delete;
    BMPParsersFabric& operator = (BMPParsersFabric&&) = delete;

private:
    const FunctionsMap m_Functions{};
};