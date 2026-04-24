#include "core/depthBuffer.h"

#include <algorithm>

DepthBuffer::DepthBuffer(unsigned int width, unsigned int height)
    : width(width), height(height), depthBuffer(width * height, -1.0f) {}

void DepthBuffer::resize(unsigned int newWidth, unsigned int newHeight) {
    width = newWidth;
    height = newHeight;
    size_t size = static_cast<size_t>(newWidth) * static_cast<size_t>(newHeight);
    depthBuffer.assign(size, -1.0f);
}

void DepthBuffer::clear(float depth) {
    std::fill(depthBuffer.begin(), depthBuffer.end(), depth);
}

bool DepthBuffer::isCloser(size_t index, float depth) const {
    return depth > depthBuffer[index];
}

void DepthBuffer::setDepth(size_t index, float depth) {
    depthBuffer[index] = depth;
}

unsigned int DepthBuffer::getWidth() const {
    return width;
}

unsigned int DepthBuffer::getHeight() const {
    return height;
}
