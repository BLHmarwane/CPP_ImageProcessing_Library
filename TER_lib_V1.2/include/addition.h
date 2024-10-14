#ifndef ADDITION_H
#define ADDITION_H

#include "Processing2.h"

namespace v1_2 {

template <typename T>
class Addition : public Processing2<T> {
public:
    // Constructeur pour additionner deux images
    Addition(v1_2::Image<T>* input1, v1_2::Image<T>* input2)
        : Processing2<T>(input1, input2) {}

    // Implémentation de la méthode Process pour effectuer l'addition
    void Process() override {
        for (size_t y = 0; y < this->inputImage1->getHeight(); ++y) {
            for (size_t x = 0; x < this->inputImage1->getWidth(); ++x) {
                this->outputImage(x, y) = std::min(
                    static_cast<T>(this->inputImage1->operator()(x, y) + this->inputImage2->operator()(x, y)),
                    std::numeric_limits<T>::max()
                );
            }
        }
    }
};

} // namespace v1_2

#endif // ADDITION_H
