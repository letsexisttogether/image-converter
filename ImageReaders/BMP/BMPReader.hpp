#pragma once

#include "ImageReaders/ImageReaderRealization.hpp"
#include "ImageFormats/BMP/BMP.hpp"

class BMPReader : public ImageReaderRealization<BMP>
{
    BMPReader(std::ifstream&& reader);

    ~BMPReader() = default; 

protected:
    void ReadHeader() noexcept override; 
    void ReadData() noexcept override;
    
    void CheckHeader() const noexcept(false) override;
    void CheckData() const noexcept(false) override;
};
