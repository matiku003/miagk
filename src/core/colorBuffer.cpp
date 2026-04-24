#include "core/colorBuffer.h"

#include <algorithm>
#include <vector>

#include "core/color.h"

ColorBuffer::ColorBuffer(unsigned int width, unsigned int height)
    : width(width), height(height), colorBuffer(width * height) {}

void ColorBuffer::resize(unsigned int newWidth, unsigned int newHeight) {
    width = newWidth;
    height = newHeight;
    size_t size = static_cast<size_t>(newWidth) * static_cast<size_t>(newHeight);
    colorBuffer.resize(size);
}

void ColorBuffer::setPixelColor(size_t index, const Color& color) {
    colorBuffer[index] = color;
}

void ColorBuffer::fill(const Color& color) {
    std::fill(colorBuffer.begin(), colorBuffer.end(), color);
}

unsigned int ColorBuffer::getWidth() const {
    return width;
}

unsigned int ColorBuffer::getHeight() const {
    return height;
}

const std::vector<Color>& ColorBuffer::getColorBuffer() const {
    return colorBuffer;
}
