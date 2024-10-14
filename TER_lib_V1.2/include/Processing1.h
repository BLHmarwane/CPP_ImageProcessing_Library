#ifndef PROCESSING1_H
#define PROCESSING1_H

#include "image.h"
namespace v1_2 {
// Classe abstraite pour les traitements avec une seule image en entrée
template <typename T>
class Processing1 {
protected:
    Image<T>* inputImage;    // Image d'entrée
    Image<T> outputImage;    // Image de sortie
    bool inPlace;            // Détermine si la modification est effectuée sur l'image d'entrée ou si une nouvelle image est créée

public:
    Processing1(Image<T>* input, bool inPlace = false)
        : inputImage(input), outputImage(input->getWidth(), input->getHeight()), inPlace(inPlace) {
        // On initialise outputImage avec la même taille que inputImage
    }

    virtual void Process() = 0;  // Fonction virtuelle pure
    Image<T>& getOutput() {
        return inPlace ? *inputImage : outputImage;
    }
};


} // namespace v1_2

#endif // PROCESSING1_H
