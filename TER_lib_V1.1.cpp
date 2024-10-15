#include <iostream>
#include "image.h"
#include "file_io.h"

int main() {
    using namespace v1_1;

    // Dimensions de l'image
    size_t width = 256;
    size_t height = 256;
/*
    // Créer une image en niveaux de gris et la remplir avec un damier
    Image<uint8_t> grayImage(width, height);
    grayImage.createCheckerboardImage(32);

    // Afficher les premiers pixels de l'image en niveaux de gris
    std::cout << "Image en niveaux de gris (damier):" << std::endl;
    for (size_t y = 0; y < 10; ++y) {
        for (size_t x = 0; x < 10; ++x) {
            std::cout << static_cast<int>(grayImage(x, y)) << " ";
        }
        std::cout << std::endl;
    }

    // Sauvegarder l'image en niveaux de gris
    std::string grayFilename = "generated_images/gray_checkerboard.raw";
    writeImage(grayFilename, grayImage, Endian::LittleEndian);
    std::cout << "L'image en niveaux de gris a été sauvegardée dans " << grayFilename << std::endl;
*/
    // Lire l'image en niveaux de gris à partir du fichier
    Image<uint8_t> loadedGrayImage(width, height);
    std::string grayFilename = "images/IRM_8_bits_256x256_coeur.raw";
    readImage(grayFilename, loadedGrayImage, Endian::LittleEndian);
    std::cout << "L'image en niveaux de gris a été lue depuis " << grayFilename << std::endl;

    // Lire une LUT à partir d'un fichier
    std::string lutFilename = "LUT/12_colors_x.lut";
    std::vector<Color> lut = readLUT(lutFilename);
    std::cout << "LUT lue depuis " << lutFilename << std::endl;

    // Créer une image RGB en appliquant la LUT à l'image en niveaux de gris
    ImageRGB colorImage(loadedGrayImage, lut);

    // Sauvegarder l'image en couleurs
    std::string colorFilename = "generated_images/color_IRM_8_bits_256x256_coeur.raw"; //!change le nom 
    std::ofstream colorFile(colorFilename, std::ios::binary);
    for (const auto& color : colorImage.getData()) {
        colorFile.write(reinterpret_cast<const char*>(&color.r), sizeof(uint8_t));
        colorFile.write(reinterpret_cast<const char*>(&color.g), sizeof(uint8_t));
        colorFile.write(reinterpret_cast<const char*>(&color.b), sizeof(uint8_t));
    }
    std::cout << "L'image en couleurs a été sauvegardée dans " << colorFilename << std::endl;

    return 0;
}
