#include <chrono>
#include <iostream>

#include "core/color.h"
#include "core/image.h"
#include "math/geometry.h"
#include "rasterizer/rasterizer.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    Image image(1024, 1024);

    Color red = {1.0f, 0.0f, 0.0f};
    Color green = {0.0f, 1.0f, 0.0f};
    Color blue = {0.0f, 0.0f, 1.0f};
    Color gray = {0.3f, 0.3f, 0.3f};

    Triangle triangle = {
        { 0.5f, -0.5f,   red},
        {-0.5f, -0.5f, green},
        { 0.0f,  0.5f,  blue}
    };

    image.fill(gray);
    Rasterizer::drawTriangle(image, triangle);
    image.saveTGA("output.tga");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms\n";

    return 0;
}
