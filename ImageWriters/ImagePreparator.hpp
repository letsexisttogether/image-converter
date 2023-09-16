#pragma once

#include "ImageFormats/ImageFormat.hpp"

template<class _ImageFormat>
class ImagePreparator
{
public: 
    ImagePreparator(ImageFormat&& image)
        : m_Image{ std::move(image) }
    {}

    virtual ~ImagePreparator() = default; 

    virtual _ImageFormat&& PrepareImage() noexcept = 0; 

protected: 
    _ImageFormat m_Image;
};
