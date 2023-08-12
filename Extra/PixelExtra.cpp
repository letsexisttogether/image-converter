#include "PixelExtra.hpp"

std::uint8_t CalculateSetBits(const std::uint8_t byte)
{
    std::uint8_t count = 0;

    for (std::uint8_t byteCopy = byte; byteCopy; byteCopy >>= 1)
    {
        count += (byteCopy & 1);
    }

    return count;
}

std::uint8_t ReverseBits(const std::uint8_t byte)
{
    std::uint8_t reversedByte{};

    for (std::uint8_t i = 0, byteSize = sizeof(byte), mask = 0x1; 
            i < byteSize; ++i)
    {
            if (byte & (mask << i)) 
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

