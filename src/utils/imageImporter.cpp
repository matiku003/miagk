#include "utils/imageImporter.h"

#include <cstdio>
#include <iostream>
#include <vector>

ColorBuffer ImageImporter::loadTGA(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        std::cerr << "Can't open file: " << filename << "\n";
        return ColorBuffer(0, 0);
    }

    unsigned char header[18];
    if (fread(header, 1, 18, file) != 18) {
        fclose(file);
        return ColorBuffer(0, 0);
    }

    unsigned int width = header[12] | (header[13] << 8);
    unsigned int height = header[14] | (header[15] << 8);
    unsigned char bitsPerPixel = header[16];
    unsigned char descriptor = header[17];

    ColorBuffer image(width, height);
    unsigned int bytesPerPixel = bitsPerPixel / 8;
    std::vector<unsigned char> pixelData(width * height * bytesPerPixel);

    if (fread(pixelData.data(), 1, pixelData.size(), file) != pixelData.size()) {
        fclose(file);
        return ColorBuffer(0, 0);
    }

    fclose(file);

    bool flipY = !(descriptor & (1 << 5));

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            unsigned int targetY = flipY ? (height - 1 - y) : y;
            unsigned int pixelIdx = (y * width + x) * bytesPerPixel;

            float b = pixelData[pixelIdx + 0] / 255.0f;
            float g = pixelData[pixelIdx + 1] / 255.0f;
            float r = pixelData[pixelIdx + 2] / 255.0f;

            image.setPixelColor(targetY * width + x, {r, g, b});
        }
    }

    std::cout << "Loaded file: " << filename << " (" << width << "x" << height << ", " << (int)bitsPerPixel << "bpp)\n";
    return image;
}
