#ifndef SYNTHETIC_IMAGES_H
#define SYNTHETIC_IMAGES_H

#include "image.h"
#include <random>

// Fonction pour générer des ellipses aléatoires avec des labels
v1_2::Image<RGB> generateSyntheticImage(size_t width, size_t height) {
    v1_2::Image<RGB> image(width, height);
    std::random_device rd;
    std::mt19937 gen(rd());

    // Distribution gaussienne pour le bruit
    std::normal_distribution<> noise(0, 15);

    // Générer quelques ellipses avec des couleurs différentes
    for (int i = 0; i < 5; ++i) {
        int centerX = rand() % width;
        int centerY = rand() % height;
        int radiusX = rand() % 50 + 20;
        int radiusY = rand() % 50 + 20;
        RGB color(rand() % 256, rand() % 256, rand() % 256);

        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                // Equation d'ellipse
                float distX = (x - centerX) / static_cast<float>(radiusX);
                float distY = (y - centerY) / static_cast<float>(radiusY);
                if (distX * distX + distY * distY <= 1) {
                    image(x, y) = RGB(
                        std::clamp(color[0] + static_cast<int>(noise(gen)), 0, 255),
                        std::clamp(color[1] + static_cast<int>(noise(gen)), 0, 255),
                        std::clamp(color[2] + static_cast<int>(noise(gen)), 0, 255)
                    );
                }
            }
        }
    }

    return image;
}

#endif // SYNTHETIC_IMAGES_H
