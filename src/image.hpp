//!------------------------------IMPLEMENTATION----------------------------------------------------
#ifndef IMAGE_FUNCTIONS_HPP
#define IMAGE_FUNCTIONS_HPP

#include "image.h"
#include <cmath>
#include <limits>
#include <algorithm>
#include <fstream>

//!============================================V1_0================================================
namespace v1_0 {

//TODO=============================================================================================
template <typename T>
std::vector<T> allocateImage(size_t width, size_t height) {
    return std::vector<T>(width * height);
}

//*================================================================================================
template <typename T>
void setImagePixel(std::vector<T>& image, size_t width, size_t x, size_t y, T value) {
    image[y * width + x] = value;
}

//*================================================================================================
template <typename T>
T getImagePixel(const std::vector<T>& image, size_t width, size_t x, size_t y) {
    return image[y * width + x];
}

//?================================================================================================
template <typename T>
void createWhiteImage(std::vector<T>& image, size_t width, size_t height) {
    std::fill(image.begin(), image.end(), std::numeric_limits<T>::max());
}
//------------------------------------------------------------------------------------------------
template <typename T>
void createCheckerboardImage(std::vector<T>& image, size_t width, size_t height, size_t blockSize) {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            image[y * width + x] = ((x / blockSize + y / blockSize) % 2 == 0) ? std::numeric_limits<T>::max() : 0;
        }
    }
}
//------------------------------------------------------------------------------------------------
template <typename T>
void createSinusoidalImage(std::vector<T>& image, size_t width, size_t height, double frequency) {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            image[y * width + x] = static_cast<T>((std::sin(2 * M_PI * frequency * x / width) + 1) * 0.5 * std::numeric_limits<T>::max());
        }
    }
}

//?==================================IMAGE CONVERTOR==================================================
template <typename SrcType, typename DstType>
std::vector<DstType> convertImage(const std::vector<SrcType>& srcImage, size_t width, size_t height, bool adjustDynamicRange) {
    std::vector<DstType> dstImage(width * height);

    if (adjustDynamicRange) {
        SrcType srcMin = *std::min_element(srcImage.begin(), srcImage.end());
        SrcType srcMax = *std::max_element(srcImage.begin(), srcImage.end());

        for (size_t i = 0; i < srcImage.size(); ++i) {
            dstImage[i] = static_cast<DstType>((srcImage[i] - srcMin) * std::numeric_limits<DstType>::max() / (srcMax - srcMin));
        }
    } else {
        for (size_t i = 0; i < srcImage.size(); ++i) {
            dstImage[i] = static_cast<DstType>(srcImage[i]);
        }
    }

    return dstImage;
}

//?=====================================================================================================
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

template <typename T>
std::vector<Color> applyLUT(const std::vector<T>& srcImage, size_t width, size_t height, const std::vector<Color>& lut) {
    std::vector<Color> dstImage(width * height);
    for (size_t i = 0; i < srcImage.size(); ++i) {
        dstImage[i] = lut[static_cast<uint8_t>(srcImage[i])];
    }
    return dstImage;
}
//!=====================================================================================================

} // namespace v1_0

#endif // IMAGE_FUNCTIONS_HPP

