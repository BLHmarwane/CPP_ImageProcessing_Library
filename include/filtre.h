#ifndef FILTERS_H
#define FILTERS_H

#include "image.h"
#include <algorithm>

namespace v1_2 {

// Filtre de convolution appliqué sur une image
template <typename T>
void applyConvolutionFilter(v1_2::Image<T>& image, const std::vector<std::vector<float>>& kernel) {
    size_t width = image.getWidth();
    size_t height = image.getHeight();
    
    // Crée une image de sortie avec les mêmes dimensions
    v1_2::Image<T> outputImage(width, height);

    int kernelSize = kernel.size();
    int kOffset = kernelSize / 2;

    // Applique la convolution du noyau sur l'image
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            float sum = 0.0;
            for (int ky = -kOffset; ky <= kOffset; ++ky) {
                for (int kx = -kOffset; kx <= kOffset; ++kx) {
                    int pixelX = std::min(std::max(int(x) + kx, 0), int(width) - 1);
                    int pixelY = std::min(std::max(int(y) + ky, 0), int(height) - 1);
                    sum += image(pixelX, pixelY) * kernel[ky + kOffset][kx + kOffset];
                }
            }
            outputImage(x, y) = std::clamp(sum, 0.0f, float(std::numeric_limits<T>::max()));
        }
    }

    // Remplace l'image d'origine par l'image filtrée
    image = outputImage;
}

}  // namespace v1_2

#endif  // FILTERS_H
