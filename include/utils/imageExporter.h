#pragma once

#include "core/colorBuffer.h"

class ImageExporter {
  public:
    /**
     * @brief Saves color buffer data in .tga file.
     *
     * The image is stored as an uncompressed 32-bit TGA (BGRA format).
     * The alpha channel is always set to fully opaque (255).
     *
     * @param image Source image to export.
     * @param filename Name of the output image in .tga format.
     */
    static void saveTGA(const ColorBuffer& image, const char* filename);
};
