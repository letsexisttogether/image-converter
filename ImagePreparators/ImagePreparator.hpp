#pragma once

class ImagePreparator
{
public: 
    virtual ~ImagePreparator() = default; 

    virtual void PrepareImage() noexcept = 0;
};
