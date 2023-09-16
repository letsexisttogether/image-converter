#pragma once

#include <utility>

#include "ImageWriter.hpp"

template<class _ImageFormat>
class ImageWriterRealization : public ImageWriter
{
public:
    ImageWriterRealization(std::ofstream&& fileWriter)
        : ImageWriter{ std::forward<std::ofstream>(fileWriter) } 
    {}

    virtual ~ImageWriterRealization() = default;

    void Write() noexcept(false) override
    {
        WriteHeader();
        WriteData();
    }

    virtual void WriteHeader() noexcept(false) = 0;
    virtual void WriteData() noexcept(false) = 0;
};
