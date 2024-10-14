#ifndef FILE_IO_H
#define FILE_IO_H

#include "image.h"
#include <fstream>
#include <stdexcept>
#include <cstddef>

namespace v1_2 {

template <typename T>
void readImage(const std::string& filename, Image<T>& image, Endian endian) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file for reading");
    }

    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            T value;
            file.read(reinterpret_cast<char*>(&value), sizeof(T));
            if (endian == Endian::BigEndian) {
                //! Convert to big endian if necessary
                if constexpr (sizeof(T) == 2) {
                    value = __builtin_bswap16(value); //! Conversion code for 16-bit values
                } else if constexpr (sizeof(T) == 4) {
                    value = __builtin_bswap32(value); //! Conversion code for 32-bit values
                }
            }
            image(x, y) = value;
        }
    }
}

template <typename T>
void writeImage(const std::string& filename, const Image<T>& image, Endian endian) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file for writing");
    }

    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            T value = image(x, y);
            if (endian == Endian::BigEndian) {
                //! Convert to big endian if necessary
                if constexpr (sizeof(T) == 2) {
                    value = __builtin_bswap16(value); //! Conversion code for 16-bit values
                } else if constexpr (sizeof(T) == 4) {
                    value = __builtin_bswap32(value); //! Conversion code for 32-bit values
                }
            }
            file.write(reinterpret_cast<const char*>(&value), sizeof(T));
        }
    }
}

} // namespace v1_2

#endif // FILE_IO_H
