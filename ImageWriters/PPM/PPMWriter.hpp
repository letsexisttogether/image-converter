#pragma once 

#include "ImageWriters/ImageWriterRealization.hpp"
#include "ImageFormats/PPM/PPM.hpp"

#include "DataCoders/PPMDataCoder.hpp"
#include "CreationalFabric/CreationalFabric.hpp"

class PPMWriter : public ImageWriterRealization<PPM>
{
public:
    using Fabric = CreationalFabric<std::string, PPMDataCoder, 
          std::ofstream&, const PPM&>;

public:
    PPMWriter(std::ofstream&& fileWriter, const PPM& image, Fabric&& fabric);

    ~PPMWriter() = default;

protected:
    void WriteHeader() noexcept(false) override;
    void WriteData() noexcept(false) override;

private:
    Fabric m_Fabric;
};
