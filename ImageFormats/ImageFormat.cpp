#include "ImageFormat.hpp"

ImageFormat::ImageFormat(ImageFormat&& imageFormat)
    : Width{ imageFormat.Width }, Height{ imageFormat.Height }, 
        Data{ std::move(imageFormat.Data) }
{}

ImageFormat::ImageFormat(const ScreenResolution width, const ScreenResolution height)
    : Width{ width }, Height{ height }, 
        Data(Height, ImageFormat::DataRow(Width))
{}

ImageFormat::ImageFormat(const ScreenResolution width, const ScreenResolution height, 
        const DataStorage& data)
    : Width{ width }, Height{ height }, Data{ data }
{}

ImageFormat::ImageFormat(const ScreenResolution width, const ScreenResolution height, 
        DataStorage&& data)
    : Width{ width }, Height{ height }, Data{ std::move(data) }
{}

const ImageFormat::CompleteResolution ImageFormat::GetResolution() const noexcept
{
    return const_cast<ImageFormat*>(this)->GetResolution();
}

ImageFormat::CompleteResolution ImageFormat::GetResolution() noexcept
{
    return { Height, Width };
}

Pixel& ImageFormat::GetPixel(const ScreenResolution height,
        const ScreenResolution width) noexcept(false)
{
    return Data.at(height).at(width);
}

const Pixel& ImageFormat::GetPixel(const ScreenResolution height,
        const ScreenResolution width) const noexcept(false)
{
    return const_cast<ImageFormat*>(this)->GetPixel(height, width);
}

ImageFormat& ImageFormat::operator = (ImageFormat&& imageFormat)
{
    Height = imageFormat.Height;
    Width = imageFormat.Width;
    Data = std::move(imageFormat.Data);

    return *this;
}

