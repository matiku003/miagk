#pragma once

#include "buffer/colorBuffer.h"

class ImageImporter {
  public:
    /**
     * @brief Loads TGA file.
     *
     * @param filename Path to the file.
     * @return ColorBuffer with TGA file data.
     */
    static ColorBuffer loadTGA(const char* filename);
};
