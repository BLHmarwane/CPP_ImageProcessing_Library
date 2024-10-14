# CPP_ImageProcessing_Library

This project is a C++ library for image processing that evolves through three versions: V1.0, V1.1, and V1.2. Each version introduces new features and improvements in image manipulation, filtering, and segmentation.

## Project Structure

- **TER_lib_V1.0/**: Basic image processing functions using dynamic arrays (`std::vector`) for image representation.
- **TER_lib_V1.1/**: Introduction of object-oriented programming (OOP) with classes and templates for better flexibility and modularity.
- **TER_lib_V1.2/**: Advanced image processing techniques, including convolution filters, Sobel edge detection, multi-thresholding, Otsu's thresholding, and K-means clustering for image segmentation.

---

### Version 1.0 - Basic Image Processing
This version focuses on basic image manipulation using dynamic arrays. It includes:
- **Image creation**: Functions to create white images, checkerboard patterns, and sinusoidal patterns.
- **File I/O**: Read and write raw images (`.raw` format), with support for big-endian and little-endian formats.
- **Basic type conversions**: Convert images between different types.
- **LUT Application**: Apply Look-Up Tables (LUTs) to grayscale images for false color representation.

---

### Version 1.1 - Object-Oriented Programming (OOP)
This version refactors the code to use object-oriented programming principles, enhancing modularity and flexibility:
- **Image class**: Encapsulates image data and operations into a template class `Image<T>`, improving reusability and clarity.
- **RGB Images**: Support for RGB image manipulation with conversion from grayscale to RGB using LUTs.
- **Overloaded operators**: The `()` operator is overloaded to simplify pixel access.

---

### Version 1.2 - Advanced Image Processing
In this version, advanced techniques are introduced:
- **Convolution filters**: Generic convolution filters to apply various effects like blurring or edge enhancement.
- **Sobel edge detection**: Detect edges in an image using the Sobel operator.
- **Thresholding**: Implement multi-thresholding and Otsu's thresholding methods for image segmentation.
- **K-means clustering**: Cluster pixel data into groups using K-means for image classification.
- **Fourier transforms**: Perform frequency domain filtering using Fast Fourier Transform (FFT).

---

## How to Compile

Each version contains a **Makefile** that automates the compilation process. Navigate to the specific version folder (e.g., `TER_lib_V1.0/`) and run:

```bash
make
```

This will generate the executable, which can be run with:

```bash
./image_processor
```

## Requirements

- **C++17**
- A compiler that supports **C++17** (e.g., GCC, Clang).

## Generated Images

Output images will be saved in the `generated_images/` directory for each version. These images can be visualized using tools like [Photopea](https://www.photopea.com/), an online image editor.
