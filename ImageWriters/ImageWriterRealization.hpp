#pragma once

#include <utility>

#include "ImageWriter.hpp"

template<class _ImageFormat>
class ImageWriterRealization : public ImageWriter
{
public:
    ImageWriterRealization(std::ofstream&& fileWriter, const ImageFormat& image, 
            const _ImageFormat& signature)
        : ImageWriter{ std::forward<std::ofstream>(fileWriter), image }, m_Signature{ signature }
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
    const _ImageFormat& m_Signature;
};
