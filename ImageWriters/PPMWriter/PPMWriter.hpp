#pragma once 

#include "../ImageWriterRealization.hpp"
#include "ImageFormats/PPM/PPM.hpp"

class PPMWriter : public ImageWriterRealization<PPM>
{
public:
    PPMWriter(std::ofstream&& fileWriter, const PPM& image);

    ~PPMWriter() = default;

protected:
    void WriteHeader() noexcept(false) override;
    void WriteData() noexcept(false) override;
};
