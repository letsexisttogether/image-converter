#pragma once

#include <algorithm>
#include <fstream>

#include "ImageFormats/ImageFormat.hpp"

class ImageWriter
{
public:
    ImageWriter(std::ofstream&& fileWriter, const ImageFormat& image)
        : m_FileWriter{ std::move(fileWriter) }, m_Image{ image }
    {}

    virtual ~ImageWriter() = default;
    
    virtual void Write() noexcept(false) = 0;

protected:
    std::ofstream m_FileWriter;
    const ImageFormat& m_Image;
};
