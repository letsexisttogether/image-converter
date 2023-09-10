#pragma once

#include "ImageReaders/ImageReaderRealization.hpp"
#include "ParsersFabric/BMPParsersFabric.hpp"

class BMPReader : public ImageReaderRealization<BMP>
{
public:
    BMPReader(std::ifstream&& reader, const BMPParsersFabric& parsersFabric);

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
    BMPParsersFabric m_Fabric;
};
