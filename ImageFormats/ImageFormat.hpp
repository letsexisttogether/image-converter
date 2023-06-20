#pragma once

#include <cstdint>
#include <vector>

class ImageFormat
{
public:
    using ScreenResolution = std::uint16_t;
    using Byte = std::uint8_t;
    using DataRow = std::vector<Byte>;
    using DataStorage = std::vector<DataRow>; 

public:
    ImageFormat(const ImageFormat&) = default;
    ImageFormat(ImageFormat&& imageFormat);
    
    ImageFormat(const ScreenResolution width, const ScreenResolution height);
    ImageFormat(const ScreenResolution width, const ScreenResolution height, const DataStorage& data);
    ImageFormat(const ScreenResolution width, const ScreenResolution height, DataStorage&& data);
    
    virtual ~ImageFormat() = default;

    Byte& GetByte(const std::size_t height, const std::size_t width) noexcept(false);
    const Byte& GetByte(const std::size_t height, const std::size_t width) const noexcept(false);

    ImageFormat& operator = (const ImageFormat&) = default;
    ImageFormat& operator = (ImageFormat&& imageFormat);

private:
    ScreenResolution m_Width;
    ScreenResolution m_Height;
    DataStorage m_Data;
};