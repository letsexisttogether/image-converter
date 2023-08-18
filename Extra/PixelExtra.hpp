#pragma once

#include <cstdint>
#include <fstream>

#include "Pixel/Pixel.hpp"

std::uint8_t CalculateSetBits(const std::uint32_t byteSet);

std::uint32_t ReverseBits(const std::uint32_t byteSet);

void ReadAsBytes(std::ifstream& stream, const std::streamsize bytesCount, 
        std::vector<Pixel::ColorValue*> colorValues);

