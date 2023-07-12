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
    ImageFormat() = default;
    ImageFormat(const ImageFormat&) = default;
    ImageFormat(ImageFormat&& imageFormat);
    
    ImageFormat(const ScreenResolution width, const ScreenResolution height);
    ImageFormat(const ScreenResolution width, const ScreenResolution height, 
            const DataStorage& data);
    ImageFormat(const ScreenResolution width, const ScreenResolution height, 
            DataStorage&& data);
    
    virtual ~ImageFormat() = default;

    const ScreenResolution& GetWidth() const noexcept;
    ScreenResolution& GetWidth() noexcept;
    
    const ScreenResolution& GetHeight() const noexcept;
    ScreenResolution& GetHeight() noexcept;
    
    DataStorage& GetData() noexcept;
    const DataStorage& GetData() const noexcept;

    Byte& GetByte(const ScreenResolution height, const ScreenResolution width)
        noexcept(false);
    const Byte& GetByte(const ScreenResolution height, const ScreenResolution width)
        const noexcept(false);

    ImageFormat& operator = (const ImageFormat&) = default;
    ImageFormat& operator = (ImageFormat&& imageFormat);

protected:
    ScreenResolution m_Width{};
    ScreenResolution m_Height{};
    DataStorage m_Data{};
};
