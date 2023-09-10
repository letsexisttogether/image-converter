#pragma once 

#include "PPMReader.hpp"

class PPMP6Reader : public PPMReader
{
public:
    PPMP6Reader(std::ifstream&& reader);

    ~PPMP6Reader() = default; 

protected:
    void ReadData(PPM& ppm) noexcept override;
    
    void CheckHeader(const PPM& ppm) const noexcept(false) override; 
};
