#pragma once

#include <fstream>

#include "ImageFormats/BMP/BMP.hpp"

class BMPDataRowReader
{
public:
    BMPDataRowReader(std::ifstream& fileStream, BMP& bmp)
        : m_FileReader{ fileStream }, m_BMP{ bmp }
    {}

    virtual ~BMPDataRowReader() = default;

    virtual void ReadNextRow() noexcept = 0; 

protected:
    std::ifstream& m_FileReader;
    BMP& m_BMP;
};
