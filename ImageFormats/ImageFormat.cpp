#include "ImageFormat.hpp"

ImageFormat::ImageFormat(ImageFormat&& imageFormat)
    : m_Width{ imageFormat.m_Width }, m_Height{ imageFormat.m_Height }, m_Data{ std::move(imageFormat.m_Data) }
{}

ImageFormat::ImageFormat(const ScreenResolution width, const ScreenResolution height)
    : m_Width{ width }, m_Height{ height }, m_Data(m_Height, ImageFormat::DataRow(m_Width))
{}

ImageFormat::ImageFormat(const ScreenResolution width, const ScreenResolution height, const DataStorage& data)
    : m_Width{ width }, m_Height{ height }, m_Data{ data }
{}

ImageFormat::ImageFormat(const ScreenResolution width, const ScreenResolution height, DataStorage&& data)
    : m_Width{ width }, m_Height{ height }, m_Data{ std::move(data) }
{}

ImageFormat::Byte& ImageFormat::GetByte(const std::size_t height, const std::size_t width) noexcept(false)
{
    return m_Data.at(height).at(width);
}

const ImageFormat::Byte& ImageFormat::GetByte(const std::size_t height, const std::size_t width) const noexcept(false)
{
    return const_cast<ImageFormat*>(this)->GetByte(height, width);
}

ImageFormat& ImageFormat::operator = (ImageFormat&& imageFormat)
{
    m_Height = imageFormat.m_Height;
    m_Width = imageFormat.m_Width;
    m_Data = std::move(imageFormat.m_Data);
}
