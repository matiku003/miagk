#include "core/framebuffer.h"

#include "core/color.h"
#include "core/colorBuffer.h"

Framebuffer::Framebuffer(unsigned int w, unsigned int h) : colorBuffer(w, h), depthBuffer(w, h) {}

void Framebuffer::clear(const Color& clearColor, float clearDepth) {
    colorBuffer.fill(clearColor);
    depthBuffer.clear(clearDepth);
}

void Framebuffer::setPixel(size_t index, float z, const Color& colorVal) {
    depthBuffer.setDepth(index, z);
    colorBuffer.setPixelColor(index, colorVal);
}

bool Framebuffer::passesDepthTest(size_t index, float z) const {
    return depthBuffer.isCloser(index, z);
}

void Framebuffer::resize(unsigned int w, unsigned int h) {
    colorBuffer.resize(w, h);
    depthBuffer.resize(w, h);
}

unsigned int Framebuffer::getWidth() const {
    return colorBuffer.getWidth();
}

unsigned int Framebuffer::getHeight() const {
    return colorBuffer.getHeight();
}

ColorBuffer& Framebuffer::getColorBuffer() {
    return colorBuffer;
}

const ColorBuffer& Framebuffer::getColorBuffer() const {
    return colorBuffer;
}
