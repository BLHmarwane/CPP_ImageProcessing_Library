#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>
#include <cstddef>

namespace v1_0 {

enum class Endian {
    BigEndian,
    LittleEndian
};
//*===================================Image Writer====================================================================
template <typename T>
void writeImage(const std::string& filename, const std::vector<T>& image, size_t width, size_t height, Endian endian);
//*===================================Image Reader====================================================================
template <typename T>
std::vector<T> readImage(const std::string& filename, size_t width, size_t height, Endian endian);

} // namespace v1_0

#include "../src/file_io.hpp"

#endif // FILE_IO_H
