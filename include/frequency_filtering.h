#ifndef FREQUENCY_FILTERING_H
#define FREQUENCY_FILTERING_H

#include "image.h"
#include "FFT.h"

namespace v1_2 {

template <typename T>
void applyFrequencyFilter(v1_2::Image<T>& image, const v1_2::Image<T>& filter) {
    size_t width = image.getWidth();
    size_t height = image.getHeight();

    v1_2::Image<T> realImage(width, height), imagImage(width, height);
    v1_2::Image<T> realFilter(width, height), imagFilter(width, height);
    v1_2::Image<T> realResult(width, height), imagResult(width, height);

    directFFT(image, imagImage, realImage, imagImage);
    directFFT(filter, imagFilter, realFilter, imagFilter);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            T realPart = realImage(x, y) * realFilter(x, y) - imagImage(x, y) * imagFilter(x, y);
            T imagPart = realImage(x, y) * imagFilter(x, y) + imagImage(x, y) * realFilter(x, y);
            realResult(x, y) = realPart;
            imagResult(x, y) = imagPart;
        }
    }

    inverseFFT(realResult, imagResult, realImage, imagImage);
    image = realImage;
}

}  // namespace v1_2

#endif  // FREQUENCY_FILTERING_H
