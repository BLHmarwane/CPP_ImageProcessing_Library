#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "image.h"
#include <vector>
#include <algorithm>

namespace v2_0 {

template <typename T>
void equalizeHistogram(v1_2::Image<T>& image) {
    size_t width = image.getWidth();
    size_t height = image.getHeight();

    //! Étape 1 : Calculer l'histogramme
    std::vector<int> histogram(std::numeric_limits<T>::max() + 1, 0);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            ++histogram[image(x, y)];
        }
    }

    //! Étape 2 : Calculer l'histogramme cumulé
    std::vector<int> cumulativeHistogram(histogram.size(), 0);
    cumulativeHistogram[0] = histogram[0];
    for (size_t i = 1; i < histogram.size(); ++i) {
        cumulativeHistogram[i] = cumulativeHistogram[i - 1] + histogram[i];
    }

    //! Étape 3 : Normaliser l'histogramme cumulé
    float scaleFactor = float(std::numeric_limits<T>::max()) / (width * height);
    for (size_t i = 0; i < cumulativeHistogram.size(); ++i) {
        cumulativeHistogram[i] = std::round(cumulativeHistogram[i] * scaleFactor);
    }

    //! Étape 4 : Appliquer la transformation à l'image
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            image(x, y) = cumulativeHistogram[image(x, y)];
        }
    }
}

}  // namespace v2_0

#endif  // HISTOGRAM_H
