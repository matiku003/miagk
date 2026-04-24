#pragma once

#include <vector>

#include "color.h"

class ColorBuffer {
  private:
    unsigned int width = 0;
    unsigned int height = 0;
    std::vector<Color> colorBuffer = {};

  public:
    /**
     * @brief Sets image resolution and initializes color buffer.
     *
     * @param width Image width.
     * @param height Image height.
     */
    ColorBuffer(unsigned int width, unsigned int height);

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
    void setPixelColor(size_t index, const Color& color);

    /**
     * @brief Fills the color buffer with a single color.
     *
     * @param color Color to fill the image with.
     */
    void fill(const Color& color);

    /**
     * @brief Returns image width.
     */
    [[nodiscard]] unsigned int getWidth() const;

    /**
     * @brief Returns image height.
     */
    [[nodiscard]] unsigned int getHeight() const;

    /**
     * @brief Returns color buffer.
     */
    const std::vector<Color>& getColorBuffer() const;
};
