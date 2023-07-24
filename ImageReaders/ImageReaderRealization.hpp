#include <utility>

#include "ImageReader.hpp"

template<class _ImageFormat>
class ImageReaderRealization : public ImageReader
{
public:
    ImageReaderRealization(std::ifstream && reader)
        : ImageReader{ std::forward<std::ifstream>(reader) }
    {}

    virtual ~ImageReaderRealization() = default;

    ImageFormat Read() noexcept(false) override
    {
        _ImageFormat image;

        ReadHeader(image);
        CheckHeader(image);

        ReadData(image); 
        CheckData(image);

        return image;
    }

protected:
    virtual void ReadHeader(_ImageFormat& image) noexcept = 0;
    virtual void ReadData(_ImageFormat& image) noexcept = 0;

    virtual void CheckHeader(const _ImageFormat& image) const noexcept(false) = 0;
    virtual void CheckData(const _ImageFormat& image) const noexcept(false) = 0;
};
