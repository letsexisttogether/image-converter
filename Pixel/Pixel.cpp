#include "Pixel.hpp"

Pixel::Pixel(const Byte red, const Byte green, const Byte blue)
    : m_Red{ red }, m_Green{ green }, m_Blue{ blue }
{}

Pixel::Byte& Pixel::GetRed() noexcept
{
    return m_Red;
}

const Pixel::Byte& Pixel::GetRed() const noexcept
{
    return const_cast<Pixel*>(this)->GetRed();
}

Pixel::Byte& Pixel::GetGreen() noexcept
{
    return m_Green;
}

const Pixel::Byte& Pixel::GetGreen() const noexcept
{
    return const_cast<Pixel*>(this)->GetGreen();
}

Pixel::Byte& Pixel::GetBlue() noexcept
{
    return m_Blue;
}

const Pixel::Byte& Pixel::GetBlue() const noexcept
{
    return const_cast<Pixel*>(this)->GetBlue();
}

const Pixel::ColorValues Pixel::GetColorValues() const noexcept
{
    return const_cast<Pixel*>(this)->GetColorValues();
}

Pixel::ColorValues Pixel::GetColorValues() noexcept
{
    return { m_Red, m_Green, m_Blue };    
}

std::ifstream& operator >> (std::ifstream& stream, Pixel& pixel)
{
    stream >> pixel.m_Red >> pixel.m_Green >> pixel.m_Blue;

    return stream;
}
