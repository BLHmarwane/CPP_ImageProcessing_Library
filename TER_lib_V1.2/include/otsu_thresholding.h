#ifndef OTSU_THRESHOLDING_H
#define OTSU_THRESHOLDING_H

#include "image.h"
#include <vector>
#include <cmath>

namespace v1_2 {

// Fonction pour calculer l'histogramme de l'image
template <typename T>
std::vector<int> calculateHistogram(const v1_2::Image<T>& image) {
    std::vector<int> histogram(256, 0);

    // Parcourir chaque pixel de l'image
    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            histogram[image(x, y)]++;
        }
    }

    return histogram;
}

// Fonction pour appliquer le seuillage d'Otsu
template <typename T>
T otsuThreshold(const v1_2::Image<T>& image) {
    //! Étape 1 : Calcul de l'histogramme
    std::vector<int> histogram = calculateHistogram(image);

    size_t totalPixels = image.getWidth() * image.getHeight();

    //! Étape 2 : Calcul des probabilités cumulées
    std::vector<float> probability(256, 0.0);
    for (int i = 0; i < 256; ++i) {
        probability[i] = static_cast<float>(histogram[i]) / totalPixels;
    }

    //! Étape 3 : Calcul des moments de classe cumulés
    std::vector<float> cumulativeSum(256, 0.0);
    std::vector<float> cumulativeMean(256, 0.0);
    cumulativeSum[0] = probability[0];
    cumulativeMean[0] = 0;

    for (int i = 1; i < 256; ++i) {
        cumulativeSum[i] = cumulativeSum[i - 1] + probability[i];
        cumulativeMean[i] = cumulativeMean[i - 1] + i * probability[i];
    }

    //! Étape 4 : Calcul de la variance inter-classe
    float globalMean = cumulativeMean[255];
    float maxVariance = 0.0;
    T optimalThreshold = 0;

    for (int t = 0; t < 256; ++t) {
        if (cumulativeSum[t] == 0 || cumulativeSum[t] == 1) {
            continue;  // Ignorer les seuils qui créent des classes vides
        }

        float weightBackground = cumulativeSum[t];
        float weightForeground = 1.0f - weightBackground;

        float meanBackground = cumulativeMean[t] / weightBackground;
        float meanForeground = (globalMean - cumulativeMean[t]) / weightForeground;

        // Variance inter-classe
        float varianceBetween = weightBackground * weightForeground * std::pow(meanBackground - meanForeground, 2);

        // Trouver la variance maximale
        if (varianceBetween > maxVariance) {
            maxVariance = varianceBetween;
            optimalThreshold = t;
        }
    }

    return optimalThreshold;
}

// Fonction pour appliquer le seuil d'Otsu sur l'image
template <typename T>
v1_2::Image<T> applyOtsuThresholding(const v1_2::Image<T>& image) {
    T threshold = otsuThreshold(image);

    // Créer une image binaire en appliquant le seuil d'Otsu
    v1_2::Image<T> outputImage(image.getWidth(), image.getHeight());

    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            outputImage(x, y) = (image(x, y) >= threshold) ? 255 : 0;
        }
    }

    return outputImage;
}

}  // namespace v1_2

#endif  // OTSU_THRESHOLDING_H
