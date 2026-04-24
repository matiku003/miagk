#include <chrono>
#include <iostream>

#include "core/color.h"
#include "core/framebuffer.h"
#include "math/geometry.h"
#include "rasterizer/rasterizer.h"
#include "utils/imageExporter.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    Framebuffer framebuffer(1024, 1024);

    Color gray = {0.3f, 0.3f, 0.3f};

    Color red = {1.0f, 0.0f, 0.0f};
    Color green = {0.0f, 1.0f, 0.0f};
    Color blue = {0.0f, 0.0f, 1.0f};

    Triangle triangle1 = {
        {-1.5f,  0.5f, 0.0f,   red},
        { 0.5f,  0.5f, 0.0f, green},
        {-0.5f, -0.5f, 0.0f,  blue}
    };

    Triangle triangle2 = {
        { 0.5f,  0.5f, 0.0f,   red},
        { 0.5f, -0.5f, 0.0f, green},
        {-0.5f, -0.5f, 0.0f,  blue}
    };

    Triangle triangle3 = {
        {-0.5f, -0.5f,  0.5f,   red},
        {-0.5f,  0.5f,  0.5f, green},
        { 1.0f,  0.0f, -0.5f,  blue}
    };

    framebuffer.clear(gray);

    Rasterizer::drawTriangle(framebuffer, triangle1);
    Rasterizer::drawTriangle(framebuffer, triangle2);
    Rasterizer::drawTriangle(framebuffer, triangle3);
    ImageExporter::saveTGA(framebuffer.getColorBuffer(), "output.tga");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms\n";

    return 0;
}
