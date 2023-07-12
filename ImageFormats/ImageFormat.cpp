#include "ImageFormat.hpp"

ImageFormat::ImageFormat(ImageFormat&& imageFormat)
    : m_Width{ imageFormat.m_Width }, m_Height{ imageFormat.m_Height }, 
        m_Data{ std::move(imageFormat.m_Data) }
{}

ImageFormat::ImageFormat(const ScreenResolution width, const ScreenResolution height)
    : m_Width{ width }, m_Height{ height }, 
        m_Data(m_Height, ImageFormat::DataRow(m_Width))
{}

ImageFormat::ImageFormat(const ScreenResolution width, const ScreenResolution height, 
        const DataStorage& data)
    : m_Width{ width }, m_Height{ height }, m_Data{ data }
{}

ImageFormat::ImageFormat(const ScreenResolution width, const ScreenResolution height, 
        DataStorage&& data)
    : m_Width{ width }, m_Height{ height }, m_Data{ std::move(data) }
{}

ImageFormat::ScreenResolution& ImageFormat::GetWidth() noexcept
{
    return m_Width;
}

const ImageFormat::ScreenResolution& ImageFormat::GetWidth() const noexcept
{
    return const_cast<ImageFormat*>(this)->GetWidth();
}

ImageFormat::ScreenResolution& ImageFormat::GetHeight() noexcept
{
    return m_Height;
}

const ImageFormat::ScreenResolution& ImageFormat::GetHeight() const noexcept
{
    return const_cast<ImageFormat*>(this)->GetHeight();
}

ImageFormat::DataStorage& ImageFormat::GetData() noexcept
{
    return m_Data;
}

const ImageFormat::DataStorage& ImageFormat::GetData() const noexcept
{
    return const_cast<ImageFormat*>(this)->GetData();
}

ImageFormat::Byte& ImageFormat::GetByte(const ScreenResolution height,
        const ScreenResolution width) noexcept(false)
{
    return m_Data.at(height).at(width);
}

const ImageFormat::Byte& ImageFormat::GetByte(const ScreenResolution height,
        const ScreenResolution width) const noexcept(false)
{
    return const_cast<ImageFormat*>(this)->GetByte(height, width);
}

ImageFormat& ImageFormat::operator = (ImageFormat&& imageFormat)
{
    m_Height = imageFormat.m_Height;
    m_Width = imageFormat.m_Width;
    m_Data = std::move(imageFormat.m_Data);

    return *this;
}

