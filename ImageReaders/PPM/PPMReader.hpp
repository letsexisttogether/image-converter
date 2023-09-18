#pragma once 

#include "ImageReaders/ImageReaderRealization.hpp"
#include "ImageFormats/PPM/PPM.hpp"

#include "CreationalFabric/CreationalFabric.hpp"
#include "DataParsers/PPMDataParser.hpp"

class __declspec(dllexport) PPMReader : public ImageReaderRealization<PPM> 
{
public:
    using Fabric = CreationalFabric<std::string, PPMDataParser, std::ifstream&, const PPM&>;

public:
    PPMReader(std::ifstream&& reader, Fabric&& fabric);

    ~PPMReader() = default; 

protected:
    void ReadHeader() noexcept override; 
    void ReadData() noexcept override;
    
    void CheckHeader() const noexcept(false) override;
    void CheckData() const noexcept(false) override;

private:
    Fabric m_Fabric;
 };