#pragma once

#include <cstdint>
#include <fstream>

#include "Pixel/Pixel.hpp"

std::uint8_t CalculateSetBits(const std::uint8_t byte);

std::uint8_t ReverseBits(const std::uint8_t byte);

void ReadAsBytes(std::ifstream& stream, const std::streamsize bytesCount, 
        std::vector<Pixel::ColorValue*> colorValues);

