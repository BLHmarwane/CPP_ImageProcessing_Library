#ifndef RGB_H
#define RGB_H

#include <array>
#include <cstdint>

class RGB {
private:
    std::array<uint8_t, 3> channels;  // Stocke les valeurs des canaux rouge, vert, bleu

public:
    RGB() : channels{0, 0, 0} {}
    RGB(uint8_t r, uint8_t g, uint8_t b) : channels{r, g, b} {}

    // Surcharge d'Opérateur [] pour accéder aux canaux
    uint8_t& operator[](size_t i) { return channels[i]; }
    const uint8_t& operator[](size_t i) const { return channels[i]; }

    // Fonction size() pour retourner le nombre de canaux (3 pour RGB)
    size_t size() const { return 3; }

    // Getters pour chaque canal
    uint8_t getR() const { return channels[0]; }
    uint8_t getG() const { return channels[1]; }
    uint8_t getB() const { return channels[2]; }
};

#endif // RGB_H
