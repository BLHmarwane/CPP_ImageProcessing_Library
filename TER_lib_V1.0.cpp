#include <iostream>
#include "image.h"
#include "file_io.h"

int main() {
    using namespace v1_0;
/*    //?   Les Tests des 4 premiers fonction
    // Allocation d'une image de 100x100 pixels
    size_t width = 100, height = 100;
    auto image = allocateImage<uint8_t>(width, height);

    // Création et Sauvegarde d'une image blanche========================================================
    createWhiteImage(image, width, height);
    std::string filename1 = "generated_images/white_image.raw";
    writeImage(filename1, image, width, height, Endian::LittleEndian);

    //===========>TEST DE CONVERTION:
    // Conversion de l'image en uint16_t avec ajustement de la dynamique
    auto convertedImage = convertImage<uint8_t, uint16_t>(image, width, height, true);
    // Sauvegarde de l'image convertie
    std::string convertedFilename = "generated_images/converted_image.raw";
    writeImage(convertedFilename, convertedImage, width, height, Endian::LittleEndian);

    std::cout << "L'image blanche a été sauvegardée dans " << filename1 << std::endl;
    std::cout << "L'image convertie a été sauvegardée dans " << convertedFilename << std::endl;
    //*==================================================================================================

    // Creation et Sauvegarde de l' image damier=========================================================
    createCheckerboardImage(image, width, height, 20);
    std::string filename2 = "generated_images/CheckerBoard_image.raw";
    writeImage(filename2, image, width, height, Endian::LittleEndian);
    std::cout << "L'image damier a été sauvegardée dans " << filename2 << std::endl;
    //*==================================================================================================

    // Creation et Sauvegarde de l' image sinus==========================================================
    size_t width = 100, height = 100;
    auto image = allocateImage<uint8_t>(width, height);
    createSinusoidalImage(image, width, height, 3.12);
    std::string filename3 = "generated_images/Sinus_image.raw";
    writeImage(filename3, image, width, height, Endian::LittleEndian);
    std::cout << "L'image sinus a été sauvegardée dans " << filename3 << std::endl;
    //*==================================================================================================
*/
    //?   Le Test de la fonction derniere (LUT)
     // Définition des dimensions de l'image à lire (à adapter selon l'image dans dossier images)
    size_t width = 512, height = 512;

    // Lire l'image en niveaux de gris depuis le dossier images
    std::string inputFilename = "images/XR_8_bits_512x512_femoral.raw";  // Remplacez par le nom de votre fichier
    auto image = readImage<uint8_t>(inputFilename, width, height, Endian::LittleEndian);

    // Charger la LUT
    std::vector<Color> lut = readLUT("LUT/amber.lut");//Choisir la lut depuis le dossier LUT fournis 

    // Appliquer la LUT à l'image
    auto colorImage = applyLUT(image, width, height, lut);

    // Sauvegarder l'image convertie dans le dossier generated_images
    std::string outputFilename = "generated_images/converted_image_lut.raw"; //! Ne pas oublier d'ajouter le _Nom d'image source
    std::ofstream colorFile(outputFilename, std::ios::binary);
    for (const auto& color : colorImage) {
        colorFile.write(reinterpret_cast<const char*>(&color.r), sizeof(uint8_t));
        colorFile.write(reinterpret_cast<const char*>(&color.g), sizeof(uint8_t));
        colorFile.write(reinterpret_cast<const char*>(&color.b), sizeof(uint8_t));
    }

    std::cout << "L'image en niveaux de gris a été lue depuis " << inputFilename << std::endl;
    std::cout << "L'image apres utilisation de lut a été sauvegardée dans " << outputFilename << std::endl;
//*/
/*     //?   Test des fonction de Lecture et Ecriture  
    size_t width = 256, height = 256;

    std::string inputFilename = "images/IRM_16_bits_256x256_crane.raw";  
    std::cout << "Tentative de lecture du fichier : " << inputFilename << std::endl;

    try {
        auto image = readImage<uint16_t>(inputFilename, width, height, Endian::LittleEndian);
        std::cout << "Fichier lu avec succès." << std::endl;

        std::cout << "Valeurs des premiers pixels de l'image lue : " << std::endl;
        for (size_t y = 0; y < 10; ++y) {
            for (size_t x = 0; x < 10; ++x) {
                std::cout << static_cast<int>(image[y * width + x]) << " ";
            }
            std::cout << std::endl;
        }

        std::string outputFilename = "generated_images/copied_crane.raw";
        writeImage(outputFilename, image, width, height, Endian::LittleEndian);

        auto copiedImage = readImage<uint16_t>(outputFilename, width, height, Endian::LittleEndian);
        std::cout << "Valeurs des premiers pixels de l'image écrite : " << std::endl;
        for (size_t y = 0; y < 10; ++y) {
            for (size_t x = 0; x < 10; ++x) {
                std::cout << static_cast<int>(copiedImage[y * width + x]) << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "L'image en niveaux de gris a été lue depuis " << inputFilename << std::endl;
        std::cout << "L'image a été sauvegardée dans " << outputFilename << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
*/    
    return 0;
}
