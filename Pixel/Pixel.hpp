#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>

class Pixel
{
public:
    using ColorValue = std::uint16_t;

public:
    static const ColorValue DefaultAlpha = 255;

public:
    ColorValue Red{};
    ColorValue Green{};
    ColorValue Blue{};
    ColorValue Alpha{ DefaultAlpha };
};

