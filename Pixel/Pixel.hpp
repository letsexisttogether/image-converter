#pragma once

#include <cstdint>
#include <fstream>

class Pixel
{
public:
    using Byte = std::uint16_t;
    using ColorValues = std::tuple<Byte, Byte, Byte>;

public:
    Pixel() = default;
    Pixel(const Pixel&) = default;
    Pixel(Pixel&&) = default;

    Pixel(const Byte red, const Byte green, const Byte blue);

    ~Pixel() = default;

    const Byte& GetRed() const noexcept;
    Byte& GetRed() noexcept;

    const Byte& GetGreen() const noexcept;
    Byte& GetGreen() noexcept;
    
    const Byte& GetBlue() const noexcept;
    Byte& GetBlue() noexcept;

    const ColorValues GetColorValues() const noexcept;
    ColorValues GetColorValues() noexcept;

    Pixel& operator = (const Pixel&) = default;
    Pixel& operator = (Pixel&&) = default;

    friend std::ifstream& operator >> (std::ifstream& stream, Pixel& pixel);

private:
    Byte m_Red{};
    Byte m_Green{};
    Byte m_Blue{};
};

