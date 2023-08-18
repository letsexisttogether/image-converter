#include "PixelExtra.hpp"

std::uint8_t CalculateSetBits(const std::uint32_t byteSet)
{
    std::uint8_t count = 0;

    for (std::uint32_t byteSetCopy = byteSet; byteSetCopy; byteSetCopy >>= 1)
    {
        count += (byteSetCopy & 1);
    }

    return count;
}

std::uint32_t ReverseBits(const std::uint32_t byteSet)
{
    std::uint32_t reversedByte{};

    for (std::uint32_t i = 0, byteSize = sizeof(byteSet), mask = 0x1; 
            i < byteSize; ++i)
    {
            if (byteSet & (mask << i)) 
            {
                reversedByte |= (mask << (byteSize - mask - i));
            }
    }

    return reversedByte;
}

void ReadAsBytes(std::ifstream& stream, const std::streamsize bytesCount, 
        std::vector<Pixel::ColorValue*> colorValues)
{
    for (auto valueRef : colorValues)
    {
        stream.read(reinterpret_cast<char*>(valueRef), bytesCount);
    }
}

