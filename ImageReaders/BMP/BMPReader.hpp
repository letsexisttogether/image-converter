#pragma once

#include "ImageFormats/BMP/BMP.hpp"
#include "ImageReaders/ImageReaderRealization.hpp"

#include "ImageReaders/BMP/DataParsers/BMPDataParser.hpp"
#include "CreationalFabric/CreationalFabric.hpp"

class __declspec(dllexport) BMPReader : public ImageReaderRealization<BMP>
{
public:
    using Fabric = CreationalFabric<BMP::BPPType, BMPDataParser, 
          std::ifstream&, const BMP&>;

public:
    BMPReader(std::ifstream&& reader, Fabric&& parsersFabric);

    ~BMPReader() = default; 

protected:
    void ReadHeader() noexcept override; 
    void ReadData() noexcept override;
    
    void CheckHeader() const noexcept(false) override;
    void CheckData() const noexcept(false) override;

private:
    void ReadColorTable() noexcept;

    void RemovePadding(const std::int32_t bytesRead) noexcept;

private:
    Fabric m_Fabric;
};
