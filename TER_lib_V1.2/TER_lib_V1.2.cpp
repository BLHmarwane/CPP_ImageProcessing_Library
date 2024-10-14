#include "include/image.h"
#include "include/file_io.h"
#include "include/RGB.h"
#include "include/kmeans.h"

int main() {
    size_t width = 256;  
    size_t height = 256;  

    // Lecture d'une image multispectrale IRM RGB
    v1_2::Image<RGB> multispectralImage(width, height);
    v1_2::readImage("images/IRM_16_bits_256x256_coeur.raw", multispectralImage, v1_2::Endian::LittleEndian);

    // l'algorithme des K-moyennes sur l'image multispectrale
    int k = 5;  // Nombre de clusters (vous pouvez ajuster selon les résultats attendus)
    std::vector<int> labels = v1_2::kMeansClustering(multispectralImage, k);

    // les résultats de la classification sous forme d'image de labels
    v1_2::Image<uint8_t> labelImage(width, height);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            labelImage(x, y) = labels[y * width + x] * (255 / k);  //*Échelle de gris pour visualiser les labels
        }
    }

    v1_2::writeImage("generated_images/kmeans_irm_labels.raw", labelImage, v1_2::Endian::LittleEndian);

    return 0;
}
