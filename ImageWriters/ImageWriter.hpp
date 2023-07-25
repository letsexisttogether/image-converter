#pragma once

#include <algorithm>
#include <fstream>

class ImageWriter
{
public:
    ImageWriter(std::ofstream&& fileWriter)
        : m_FileWriter{ std::move(fileWriter) }
    {}

    virtual ~ImageWriter() = default;
    
    virtual void Write() noexcept(false) = 0;

protected:
    std::ofstream m_FileWriter;
};
