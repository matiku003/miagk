
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "core/image.h"

#include <algorithm>
#include <iostream>

#include "external/stb_image_write.h"

#include "core/color.h"

Image::Image(unsigned int w, unsigned int h) : width(w), height(h), colorBuffer(w * h) {}

unsigned int Image::getWidth() const {
    return width;
}

unsigned int Image::getHeight() const {
    return height;
}

void Image::resize(unsigned int newWidth, unsigned int newHeight) {
    width = newWidth;
    height = newHeight;
    size_t size = static_cast<size_t>(width) * static_cast<size_t>(height);
    colorBuffer.resize(size);
}

void Image::setPixelColor(unsigned int index, const Color& color) {
    if (index < colorBuffer.size()) {
        colorBuffer[index] = color;
    }
}

void Image::fill(const Color& color) {
    std::fill(colorBuffer.begin(), colorBuffer.end(), color);
}

void Image::saveTGA(const char* filename) const {
    stbi_write_tga(filename, width, height, 3, colorBuffer.data());
    std::cout << "Image saved as " << filename << "\n";
}
