#ifndef THRESHOLDING_H
#define THRESHOLDING_H

#include "image.h"
#include <vector>

namespace v1_2 {

// Appliquer le multi-seuillage à une image
template <typename T>
v1_2::Image<T> applyMultiThresholding(const v1_2::Image<T>& image, const std::vector<T>& thresholds) {
    size_t width = image.getWidth();
    size_t height = image.getHeight();

    // Créer une image de sortie
    v1_2::Image<T> outputImage(width, height);

    // Parcourir chaque pixel de l'image
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            T pixelValue = image(x, y);
            
            // Appliquer le multi-seuillage en fonction des seuils
            if (pixelValue <= thresholds[0]) {
                outputImage(x, y) = 0;  // Valeurs inférieures au premier seuil
            } else if (pixelValue <= thresholds[1]) {
                outputImage(x, y) = 85;  // Entre le premier et le deuxième seuil 
            } else if (pixelValue <= thresholds[2]) {
                outputImage(x, y) = 170;  // Entre le deuxième et le troisième seuil 
            } else {
                outputImage(x, y) = 255;  // Valeurs supérieures au troisième seuil 
            }
        }
    }

    return outputImage;
}

}  // namespace v1_2

#endif  // THRESHOLDING_H
