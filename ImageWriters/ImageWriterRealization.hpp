#pragma once

#include <utility>

#include "ImageWriter.hpp"

template<class _ImageFormat>
class ImageWriterRealization : public ImageWriter
{
public:
    ImageWriterRealization(std::ofstream&& fileWriter, const _ImageFormat& image)
        : ImageWriter{ std::forward<std::ofstream>(fileWriter) }, m_Image{ image }
    {}

    virtual ~ImageWriterRealization() = default;

    void Write() noexcept(false) override
    {
        WriteHeader();
        WriteData();
    }

    virtual void WriteHeader() noexcept(false) = 0;
    virtual void WriteData() noexcept(false) = 0;

protected:
    const _ImageFormat& m_Image;
};
