#pragma once

#include <cstdint>
#include <fstream>

class Pixel
{
public:
    using ColorValue = std::uint16_t;

public:
    ColorValue Red{};
    ColorValue Green{};
    ColorValue Blue{};
    ColorValue Alpha{ 255 };
};

