#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include "file_io.h"
#include <fstream>
#include <vector>
#include <stdexcept>

namespace v1_0 {
//*=====================================================================================================================
template <typename T>
void writeImage(const std::string& filename, const std::vector<T>& image, size_t width, size_t height, Endian endian) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file for writing");
    }

    std::vector<T> data = image;
    if (endian == Endian::BigEndian) {
        for (auto& val : data) {
            val = __builtin_bswap16(val);
        }
    }

    file.write(reinterpret_cast<const char*>(data.data()), width * height * sizeof(T));
}
//*====================================================================================================================
template <typename T>
std::vector<T> readImage(const std::string& filename, size_t width, size_t height, Endian endian) {
    std::vector<T> image(width * height);
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file for reading");
    }

    file.read(reinterpret_cast<char*>(image.data()), width * height * sizeof(T));
    if (endian == Endian::BigEndian) {
        for (auto& val : image) {
            val = __builtin_bswap16(val);
        }
    }

    return image;
}

} // namespace v1_0

#endif // FILE_IO_HPP
