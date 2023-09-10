#pragma once 

#include "../ImageReaderRealization.hpp"
#include "ImageFormats/PPM/PPM.hpp"

class PPMReader : public ImageReaderRealization<PPM> 
{
public:
    PPMReader(std::ifstream&& reader);

    ~PPMReader() = default; 

protected:
    void ReadHeader(PPM& ppm) noexcept override; 
    void ReadData(PPM& ppm) noexcept override;
    
    void CheckHeader(const PPM& ppm) const noexcept(false) override;
    void CheckData(const PPM& ppm) const noexcept(false) override;
 };