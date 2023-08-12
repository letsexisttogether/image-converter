#pragma once

#include "BMPDataRowReader.hpp"

class BMP8DataRowReader : public BMPDataRowReader
{
public:
    BMP8DataRowReader(std::ifstream& fileReader, BMP& bmp, const std::uint8_t xorMask);

    void ReadNextRow() noexcept override;

private:
    void ReadColorTable() noexcept;
    
private:
    std::vector<Pixel> m_ColorTable{};
    const std::uint8_t m_XORMask;
};
