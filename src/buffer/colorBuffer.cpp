#include "buffer/colorBuffer.h"

#include <algorithm>
#include <vector>

#include "math/vector.h"

ColorBuffer::ColorBuffer(unsigned int width, unsigned int height)
    : width(width), height(height), colorBuffer(width * height) {}

void ColorBuffer::resize(unsigned int newWidth, unsigned int newHeight) {
    width = newWidth;
    height = newHeight;
    size_t size = static_cast<size_t>(newWidth) * static_cast<size_t>(newHeight);
    colorBuffer.resize(size);
}

void ColorBuffer::setPixelColor(size_t index, const float3& color) {
    colorBuffer[index] = color;
}

float3 ColorBuffer::getPixelColor(unsigned int x, unsigned int y) const {
    return colorBuffer[y * width + x];
}

void ColorBuffer::fill(const float3& color) {
    std::fill(colorBuffer.begin(), colorBuffer.end(), color);
}

unsigned int ColorBuffer::getWidth() const {
    return width;
}

unsigned int ColorBuffer::getHeight() const {
    return height;
}

const std::vector<float3>& ColorBuffer::getColorBuffer() const {
    return colorBuffer;
}

float3 ColorBuffer::sample(float u, float v) const {
    u = std::max(0.0f, std::min(1.0f, u));
    v = std::max(0.0f, std::min(1.0f, v));

    unsigned int x = static_cast<unsigned int>(u * (width - 1));
    unsigned int y = static_cast<unsigned int>(v * (height - 1));

    return getPixelColor(x, y);
}
