#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <vector>

struct Color {
    unsigned char r, g, b;
};

std::vector<Color> fill_image(const int image_width, const int image_height, Color color) {
    return std::vector<Color>(image_width * image_height, color);
}

void save_image(const int image_width, const int image_height, std::vector<Color> color_buffer) {
    stbi_write_png("output_image.jpg", image_width, image_height, 3, color_buffer.data(), image_width * 3);
    std::cout << "Image saved as output_image.jpg" << std::endl;
}

int main() {
    int image_width = 256;
    int image_height = 256;
    Color color = { 0, 128, 255 };

    std::vector<Color> color_buffer = fill_image(image_width, image_height, color);
    save_image(image_width, image_height, color_buffer);

    return 0;
}
