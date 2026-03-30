#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image.h"
#include "stb_image_write.h"
#include <iostream>

Image::Image(int w, int h) : width(w), height(h), colorBuffer(w * h) {}

void Image::fill(const Color& color) {
    std::fill(colorBuffer.begin(), colorBuffer.end(), color);
}

void Image::saveTGA(const char* filename) const {
    stbi_write_tga(filename, width, height, 3, colorBuffer.data());
    std::cout << "Image saved as " << filename << "\n";
}
