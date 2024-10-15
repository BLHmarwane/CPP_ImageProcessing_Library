#ifndef PROCESSING2_H
#define PROCESSING2_H

#include "image.h"

namespace v1_2 {

template <typename T>
class Processing2 {
protected:
    v1_2::Image<T>* inputImage1;   // Première image d'entrée
    v1_2::Image<T>* inputImage2;   // Deuxième image d'entrée
    v1_2::Image<T> outputImage;    // Image de sortie

public:
    // Constructeur prenant deux pointeurs vers des images
    Processing2(v1_2::Image<T>* input1, v1_2::Image<T>* input2)
        : inputImage1(input1), inputImage2(input2), outputImage(input1->getWidth(), input1->getHeight()) {}

    // Méthode virtuelle pure à implémenter par les classes filles
    virtual void Process() = 0;

    // Accès à l'image de sortie
    v1_2::Image<T>& getOutput() {
        return outputImage;
    }

    // Méthode pour effectuer le traitement et mettre à jour l'image de sortie
    void Update() {
        Process();  // Appelle la méthode spécifique implémentée dans la classe fille
    }
};

} // namespace v1_2

#endif // PROCESSING2_H
