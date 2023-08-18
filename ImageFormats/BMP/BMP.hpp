#pragma once 

#include "../ImageFormat.hpp"

class BMP : public ImageFormat
{
public:
    BMP() = default;
    BMP(const BMP&) = default;
    BMP(BMP&& bmp) = default;
    
    ~BMP() = default;

    BMP& operator = (const BMP&) = default;
    BMP& operator = (BMP&&) = default;
    
public:
    // Bitmap file header
    std::string HeaderField{};
    std::uint32_t FileSize{};
    std::uint16_t Reserved[2]{};
    std::uint16_t DataOffset{};

    // DIB (bitmap information) header
    std::uint32_t InfoHeaderSize{};
    std::uint16_t ColorPlanesNumber{};
    std::uint16_t BitsPerPixel{};
    std::uint32_t CompressionMethod{};
    std::uint32_t ImageSize{};
    std::uint32_t HorizontalResolution{};
    std::uint32_t VertivalResolution{};
    std::uint32_t ColorPaletteNumber{};
    std::uint32_t ImportantColorsNumber{};

    ImageFormat::DataRow ColorTable{};
};
