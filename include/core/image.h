#pragma once

#include <vector>

#include "color.h"

class Image {
  private:
    unsigned int width = 1024;
    unsigned int height = 1024;
    std::vector<Color> colorBuffer = {};

  public:
    /**
     * @brief Sets image resolution and initializes color buffer.
     *
     * @param width Image width.
     * @param height Image height.
     */
    Image(unsigned int width, unsigned int height);

    /**
     * @brief Returns image width.
     *
     * @return Image width in pixels.
     */
    [[nodiscard]] unsigned int getWidth() const;

    /**
     * @brief Returns image height.
     *
     * @return Image height in pixels.
     */
    [[nodiscard]] unsigned int getHeight() const;

    /**
     * @brief Resizes the image and reinitializes the color buffer.
     *
     * @param newWidth New image width.
     * @param newHeight New image height.
     */
    void resize(unsigned int newWidth, unsigned int newHeight);

    /**
     * @brief Sets pixel color using index.
     *
     * @param index Index in row-major buffer (y * width + x).
     * @param color Color to set.
     */
    void setPixelColor(unsigned int index, const Color& color);

    /**
     * @brief Fills the color buffer with a single color.
     *
     * @param color Color to fill the image with.
     */
    void fill(const Color& color);

    /**
     * @brief Saves color buffer data in .tga file.
     *
     * The image is stored as an uncompressed 32-bit TGA (BGRA format).
     * The alpha channel is always set to fully opaque (255).
     *
     * @param filename Name of the output image in .tga format.
     */
    void saveTGA(const char* filename) const;
};
