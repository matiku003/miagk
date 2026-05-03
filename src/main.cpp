#include <chrono>
#include <iostream>

#include "core/framebuffer.h"
#include "math/geometry.h"
#include "math/pipeline.h"
#include "math/transform.h"
#include "math/vector.h"
#include "rasterizer/rasterizer.h"
#include "utils/imageExporter.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    TransformSystem transform;

    transform.setPerspective(60.0f, 1.0f, 0.1f, 100.0f);

    transform.setLookAt({0, 0, 3}, {0, 0, 0}, {0, 1, 0});

    Framebuffer framebuffer(1024, 1024);

    float3 gray = {0.3f, 0.3f, 0.3f};

    float3 red = {1.0f, 0.0f, 0.0f};
    float3 green = {0.0f, 1.0f, 0.0f};
    float3 blue = {0.0f, 0.0f, 1.0f};
    float3 vertexA = {1.0f, -1.0f, 0.0f};
    float3 vertexB = {-1.0f, -1.0f, 0.0f};
    float3 vertexC = {0.0f, 1.0f, 0.0f};

    Triangle triangle = {applyMVP(transform, Point(vertexA, red)),
                         applyMVP(transform, Point(vertexB, green)),
                         applyMVP(transform, Point(vertexC, blue))};

    framebuffer.clear(gray);

    Rasterizer::drawTriangle(framebuffer, triangle);
    ImageExporter::saveTGA(framebuffer.getColorBuffer(), "output.tga");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms\n";

    return 0;
}
