#pragma once 

#include "ImageWriters/ImageWriterRealization.hpp"
#include "ImageFormats/PPM/PPM.hpp"
#include "ImageWriters/ImagePreparator.hpp"

#include "DataCoders/PPMDataCoder.hpp"
#include "CreationalFabric/CreationalFabric.hpp"

class PPMWriter : public ImageWriterRealization<PPM>
{
public:
    using Fabric = CreationalFabric<std::string, PPMDataCoder, 
          std::ofstream&, const PPM&>;

public:
    PPMWriter(std::ofstream&& fileWriter, 
            ImagePreparator<PPM>&& preparator, Fabric&& fabric);

    ~PPMWriter() = default;

protected:
    void WriteHeader() noexcept(false) override;
    void WriteData() noexcept(false) override;

private:
    const PPM m_Image;
    Fabric m_Fabric;
};
