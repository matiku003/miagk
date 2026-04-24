#pragma once

#include "color.h"
#include "colorBuffer.h"
#include "depthBuffer.h"

class Framebuffer {
  private:
    ColorBuffer colorBuffer;
    DepthBuffer depthBuffer;

  public:
    /**
     * @brief Creates a framebuffer with given resolution.
     *
     * @param w Width in pixels.
     * @param h Height in pixels.
     */
    Framebuffer(unsigned int w, unsigned int h);

    /**
     * @brief Clears both color and depth buffers.
     *
     * @param clearColor Color used to clear the color buffer.
     * @param clearDepth Value used to clear the depth buffer.
     */
    void clear(const Color& clearColor, float clearDepth = -1.0f);

    /**
     * @brief Writes a pixel.
     *
     * @param index Pixel index (y * width + x).
     * @param z Depth value of the pixel.
     * @param color Color to write.
     */
    void setPixel(size_t index, float z, const Color& color);

    /**
     * @brief Performs depth comparison for a pixel.
     *
     * @param index Pixel index (y * width + x).
     * @param z Depth value to test.
     * @return true if pixel is closer and should pass.
     */
    bool passesDepthTest(size_t index, float z) const;

    /**
     * @brief Resizes framebuffer and underlying buffers.
     *
     * @param newWidth New width in pixels.
     * @param newHeight New height in pixels.
     */
    void resize(unsigned int newWidth, unsigned int newHeight);

    /**
     * @brief Returns framebuffer width.
     */
    unsigned int getWidth() const;

    /**
     * @brief Returns framebuffer height.
     */
    unsigned int getHeight() const;

    /**
     * @brief Access to color buffer (mutable).
     */
    ColorBuffer& getColorBuffer();

    /**
     * @brief Access to color buffer (read-only).
     */
    const ColorBuffer& getColorBuffer() const;
};
