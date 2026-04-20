#include "core/image.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

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
    unsigned short header[9] = {0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0100, 0x0100, 0x0820};

    FILE* file = fopen(filename, "wb+");
    if (file == NULL) {
        return;
    }

    header[6] = width;
    header[7] = height;

    std::vector<unsigned char> buffer(width * height * 4);

    for (size_t i = 0; i < colorBuffer.size(); i++) {
        buffer[i * 4 + 0] = (unsigned char)(std::clamp(colorBuffer[i].b, 0.0f, 1.0f) * 255.0f);
        buffer[i * 4 + 1] = (unsigned char)(std::clamp(colorBuffer[i].g, 0.0f, 1.0f) * 255.0f);
        buffer[i * 4 + 2] = (unsigned char)(std::clamp(colorBuffer[i].r, 0.0f, 1.0f) * 255.0f);
        buffer[i * 4 + 3] = 255;
    }

    fwrite(header, 2, 9, file);
    fwrite(buffer.data(), 4, colorBuffer.size(), file);

    fclose(file);

    std::cout << "Image saved as " << filename << "\n";
}
