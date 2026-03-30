#include "image.h"
#include "renderer.h"
#include <chrono>
#include <iostream>
#include <vector>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    Image image(256, 256);

    Color color = {255, 0, 0};
    Color reverseColor = {static_cast<unsigned char>(255 - color.r),
                          static_cast<unsigned char>(255 - color.g),
                          static_cast<unsigned char>(255 - color.b)};

    Triangle triangle = {
        {-0.5, -0.5},
        { 0.5, -0.5},
        {   0,  0.5}
    };

    image.fill(color);
    Renderer::drawTriangle(image, triangle, reverseColor);
    image.saveTGA("output.tga");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms\n";

    return 0;
}
