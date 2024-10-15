#ifndef SOBEL_FILTER_H
#define SOBEL_FILTER_H

#include <vector>
#include <cmath>
#include "image.h"
#include "filtre.h"

namespace v1_2 {

// Matrices Sobel pour X et Y
const std::vector<std::vector<float>> sobelX = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

const std::vector<std::vector<float>> sobelY = {
    {-1, -2, -1},
     {0,  0,  0},
     {1,  2,  1}
};

// Fonction template pour appliquer le filtre Sobel
template <typename T>
v1_2::Image<T> applySobelFilter(const v1_2::Image<T>& image) {
    size_t width = image.getWidth();
    size_t height = image.getHeight();

    // Créer des images pour les gradients Gx et Gy
    v1_2::Image<T> gradX(image);
    v1_2::Image<T> gradY(image);

    // Appliquer la convolution pour obtenir Gx et Gy
    applyConvolutionFilter(gradX, sobelX);  // Convolution Sobel X
    applyConvolutionFilter(gradY, sobelY);  // Convolution Sobel Y

    // Créer une image pour la norme du gradient
    v1_2::Image<T> gradientMagnitude(width, height);

    // Calculer la norme du gradient pour chaque pixel
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            float gx = static_cast<float>(gradX(x, y));
            float gy = static_cast<float>(gradY(x, y));
            gradientMagnitude(x, y) = static_cast<T>(std::sqrt(gx * gx + gy * gy));
        }
    }

    return gradientMagnitude;  // Retourner l'image avec la norme du gradient
}

}  // namespace v1_2

#endif  // SOBEL_FILTER_H
