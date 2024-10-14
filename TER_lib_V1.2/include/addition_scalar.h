#ifndef ADDITION_SCALAR_H
#define ADDITION_SCALAR_H

#include "Processing1.h"
#include "image.h"  

namespace v1_2 {

template <typename T>
class AdditionScalar : public v1_2::Processing1<T> {
private:
    T scalar;  

public:
    // Constructeur avec image d'entrée et valeur scalaire
    AdditionScalar(v1_2::Image<T>* inputImage, T scalarValue)
        : v1_2::Processing1<T>(inputImage), scalar(scalarValue) {}

    // Méthode pour effectuer l'addition du scalaire à l'image 
    void Process() override {
        for (size_t y = 0; y < this->inputImage->getHeight(); ++y) {
            for (size_t x = 0; x < this->inputImage->getWidth(); ++x) {
                // Ajout du scalaire au pixel (x, y) de l'image
                this->outputImage(x, y) = this->inputImage->operator()(x, y) + scalar;
            }
        }
    }
};

}  // namespace v1_2

#endif  // ADDITION_SCALAR_H
