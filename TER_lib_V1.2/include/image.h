#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstdint> //* Inclusion pour uint8_t, uint16_t, ...
#include <fstream> //* Pour readLUT
#include <iostream> //* Pour le débogage

namespace v1_2 {  

struct Color {
    uint8_t r, g, b;
};

enum class Endian {
    LittleEndian,
    BigEndian
};

template <typename T>
class Image {
private:
    size_t m_width, m_height;
    std::vector<T> m_data;

public:
    Image(size_t width, size_t height);

    T& operator()(size_t x, size_t y);
    const T& operator()(size_t x, size_t y) const;

    void fill(T value);
    void createWhiteImage();
    void createCheckerboardImage(size_t blockSize);
    void createSinusoidalImage(double frequency);

    std::vector<T> convertToType(bool adjustDynamicRange) const;

    size_t getWidth() const { return m_width; }
    size_t getHeight() const { return m_height; }
    const std::vector<T>& getData() const { return m_data; }

};

// Classe dérivée pour la gestion des images en couleurs 
class ImageRGB : public Image<Color> {
public:
    ImageRGB(size_t width, size_t height);
    ImageRGB(const Image<uint8_t>& grayImage, const std::vector<Color>& lut);
};

// Fonction pour lire une LUT (Look-Up Table) pour fausses couleurs
std::vector<Color> readLUT(const std::string& filename);


// ===================== Implémentation de la classe Image<T> =====================

template <typename T>
Image<T>::Image(size_t width, size_t height) 
    : m_width(width), m_height(height), m_data(width * height) {}

template <typename T>
T& Image<T>::operator()(size_t x, size_t y) {
    if (x >= m_width || y >= m_height) {
        throw std::out_of_range("Pixel coordinates out of range");
    }
    return m_data[y * m_width + x];
}

template <typename T>
const T& Image<T>::operator()(size_t x, size_t y) const {
    if (x >= m_width || y >= m_height) {
        throw std::out_of_range("Pixel coordinates out of range");
    }
    return m_data[y * m_width + x];
}

template <typename T>
void Image<T>::fill(T value) {
    std::fill(m_data.begin(), m_data.end(), value);
}

template <typename T>
void Image<T>::createWhiteImage() {
    fill(std::numeric_limits<T>::max());
}

template <typename T>
void Image<T>::createCheckerboardImage(size_t blockSize) {
    for (size_t y = 0; y < m_height; ++y) {
        for (size_t x = 0; x < m_width; ++x) {
            (*this)(x, y) = ((x / blockSize + y / blockSize) % 2 == 0) ? std::numeric_limits<T>::max() : 0;
        }
    }
}

template <typename T>
void Image<T>::createSinusoidalImage(double frequency) {
    for (size_t y = 0; y < m_height; ++y) {
        for (size_t x = 0; x < m_width; ++x) {
            (*this)(x, y) = static_cast<T>((std::sin(2 * M_PI * frequency * x / m_width) + 1) * 0.5 * std::numeric_limits<T>::max());
        }
    }
}

template <typename T>
std::vector<T> Image<T>::convertToType(bool adjustDynamicRange) const {
    std::vector<T> convertedImage(m_width * m_height);
    if (adjustDynamicRange) {
        T srcMin = *std::min_element(m_data.begin(), m_data.end());
        T srcMax = *std::max_element(m_data.begin(), m_data.end());

        for (size_t i = 0; i < m_data.size(); ++i) {
            convertedImage[i] = static_cast<T>((m_data[i] - srcMin) * std::numeric_limits<T>::max() / (srcMax - srcMin));
        }
    } else {
        for (size_t i = 0; i < m_data.size(); ++i) {
            convertedImage[i] = static_cast<T>(m_data[i]);
        }
    }

    return convertedImage;
}

// ===================== Implémentation de la classe ImageRGB =====================

ImageRGB::ImageRGB(size_t width, size_t height) : Image(width, height) {}

ImageRGB::ImageRGB(const Image<uint8_t>& grayImage, const std::vector<Color>& lut) 
    : Image(grayImage.getWidth(), grayImage.getHeight()) {
    for (size_t y = 0; y < grayImage.getHeight(); ++y) {
        for (size_t x = 0; x < grayImage.getWidth(); ++x) {
            (*this)(x, y) = lut[grayImage(x, y)];
        }
    }
}

// ===================== Implémentation de la fonction readLUT =====================

std::vector<Color> readLUT(const std::string& filename) {
    std::vector<Color> lut(256);
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open LUT file");
    }

    for (int i = 0; i < 256; ++i) {
        if (!(file.read(reinterpret_cast<char*>(&lut[i].r), sizeof(uint8_t)) &&
              file.read(reinterpret_cast<char*>(&lut[i].g), sizeof(uint8_t)) &&
              file.read(reinterpret_cast<char*>(&lut[i].b), sizeof(uint8_t)))) {
            throw std::runtime_error("Error reading LUT file");
        }
    }

    return lut;
}

} // namespace v1_2

#endif // IMAGE_H
