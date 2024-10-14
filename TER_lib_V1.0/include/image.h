//!-------------------------------IMAGE FONCTIONS----------------------------------------------------
#ifndef IMAGE_FUNCTIONS_H
#define IMAGE_FUNCTIONS_H

#include <vector>
#include <cstdint>
#include <cstddef>

//!============================================V1_0================================================
namespace v1_0 {

//TODO==============================IMAGE ALLOCATION===============================================
template <typename T>
std::vector<T> allocateImage(size_t width, size_t height);

//*==============================SETTER============================================================
template <typename T>
void setImagePixel(std::vector<T>& image, size_t width, size_t x, size_t y, T value);
//*==============================GETTER============================================================
template <typename T>
T getImagePixel(const std::vector<T>& image, size_t width, size_t x, size_t y);

//?==============================IMAGE GENERATORS==================================================
template <typename T>
void createWhiteImage(std::vector<T>& image, size_t width, size_t height);

template <typename T>
void createCheckerboardImage(std::vector<T>& image, size_t width, size_t height, size_t blockSize);

template <typename T>
void createSinusoidalImage(std::vector<T>& image, size_t width, size_t height, double frequency);

//?============================IMAGE CONVERTOT===================================================
template <typename SrcType, typename DstType>
std::vector<DstType> convertImage(const std::vector<SrcType>& srcImage, size_t width, size_t height, bool adjustDynamicRange = false);

//!===========================LUTS===============================================================
struct Color {
    uint8_t r, g, b;
};

std::vector<Color> readLUT(const std::string& filename);

template <typename T>
std::vector<Color> applyLUT(const std::vector<T>& srcImage, size_t width, size_t height, const std::vector<Color>& lut);

} // namespace v1_0

#include "../src/image.hpp"

#endif // IMAGE_FUNCTIONS_H
