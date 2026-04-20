
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "core/image.h"

#include <algorithm>
#include <iostream>
#include <vector>

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
    std::vector<unsigned char> buffer(width * height * 3);

    for (size_t i = 0; i < colorBuffer.size(); i++) {
        buffer[i * 3 + 0] = (unsigned char)(std::clamp(colorBuffer[i].r, 0.0f, 1.0f) * 255.0f);
        buffer[i * 3 + 1] = (unsigned char)(std::clamp(colorBuffer[i].g, 0.0f, 1.0f) * 255.0f);
        buffer[i * 3 + 2] = (unsigned char)(std::clamp(colorBuffer[i].b, 0.0f, 1.0f) * 255.0f);
    }

    stbi_write_tga(filename, (int)width, (int)height, 3, buffer.data());
    std::cout << "Image saved as " << filename << "\n";
}
