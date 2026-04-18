#pragma once

#include <vector>

#include "color.h"

class Image {
  public:
    int width = 256;
    int height = 256;
    std::vector<Color> colorBuffer = {};

    /**
     * @brief Sets image resolution and initializes color buffer.
     *
     * @param width Image width.
     * @param height Image height.
     */
    Image(int width, int height);

    /**
     * @brief Fills color_buffer with single color.
     *
     * @param color Color to fill the image with.
     */
    void fill(const Color& color);

    /**
     * @brief Saves color buffer data in .tga file.
     *
     * @param filename Name of the output image in .tga format.
     */
    void saveTGA(const char* filename) const;
};
