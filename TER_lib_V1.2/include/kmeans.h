#ifndef KMEANS_H
#define KMEANS_H

#include "image.h"
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>  // Pour rand()

namespace v1_2 {

// Fonction de calcul de la distance euclidienne entre deux pixels RGB
float euclideanDistance(const RGB& a, const RGB& b) {
    float distance = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        distance += std::pow(static_cast<float>(a[i]) - b[i], 2);
    }
    return std::sqrt(distance);
}

// Implémentation de l'algorithme des K-moyennes
std::vector<int> kMeansClustering(const v1_2::Image<RGB>& image, int k, int maxIterations = 100) {
    size_t width = image.getWidth();
    size_t height = image.getHeight();
    size_t numPixels = width * height;

    // Initialiser les centres de clusters (aléatoirement parmi les pixels)
    std::vector<RGB> centroids(k);
    for (int i = 0; i < k; ++i) {
        size_t randX = rand() % width;
        size_t randY = rand() % height;
        centroids[i] = image(randX, randY);
    }

    // Vecteur pour stocker le cluster de chaque pixel
    std::vector<int> labels(numPixels, 0);

    for (int iter = 0; iter < maxIterations; ++iter) {
        //! Étape 1 : Assignation des pixels au centre de cluster le plus proche
        bool labelsChanged = false;

        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                RGB pixel = image(x, y);
                float minDistance = std::numeric_limits<float>::max();
                int bestCluster = 0;

                for (int i = 0; i < k; ++i) {
                    float distance = euclideanDistance(pixel, centroids[i]);
                    if (distance < minDistance) {
                        minDistance = distance;
                        bestCluster = i;
                    }
                }

                size_t pixelIndex = y * width + x;
                if (labels[pixelIndex] != bestCluster) {
                    labelsChanged = true;
                    labels[pixelIndex] = bestCluster;
                }
            }
        }

        //* Si aucune étiquette n'a changé, on arrête (convergence)
        if (!labelsChanged) {
            break;
        }

        //! Étape 2 : Mise à jour des centres de clusters
        std::vector<RGB> newCentroids(k, RGB(0, 0, 0));
        std::vector<int> clusterSizes(k, 0);

        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                int cluster = labels[y * width + x];
                newCentroids[cluster][0] += image(x, y)[0];
                newCentroids[cluster][1] += image(x, y)[1];
                newCentroids[cluster][2] += image(x, y)[2];
                clusterSizes[cluster]++;
            }
        }

        for (int i = 0; i < k; ++i) {
            if (clusterSizes[i] > 0) {
                newCentroids[i][0] /= clusterSizes[i];
                newCentroids[i][1] /= clusterSizes[i];
                newCentroids[i][2] /= clusterSizes[i];
            }
        }

        centroids = newCentroids;
    }

    return labels;
}

}  // namespace v1_2

#endif  // KMEANS_H
