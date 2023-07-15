#pragma once 

#include <fstream>

#include "../ImageFormats/ImageFormat.hpp"

class ImageReader
{
public:
    ImageReader(std::ifstream&& reader)
        : m_FileReader{ std::move(reader) }
    {}

    virtual ~ImageReader() = default;

    virtual ImageFormat Read() noexcept(false) = 0;

protected:
    std::ifstream m_FileReader;
};
