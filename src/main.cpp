#include <chrono>
#include <iostream>

#include "core/framebuffer.h"
#include "math/geometry.h"
#include "math/pipeline.h"
#include "math/transform.h"
#include "math/vector.h"
#include "rasterizer/rasterizer.h"
#include "utils/imageExporter.h"

static void draw(Framebuffer& framebuffer, const TransformSystem& transform, Point a, Point b, Point c) {
    Rasterizer::drawTriangle(framebuffer,
                             Triangle{applyMVP(transform, a), applyMVP(transform, b), applyMVP(transform, c)});
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    TransformSystem transform;

    transform.setPerspective(60.0f, 1.0f, 0.1f, 100.0f);

    transform.setLookAt({3, 3, 3}, {0, 0, 0}, {0, 1, 0});

    Framebuffer framebuffer(1024, 1024);

    float3 gray = {0.3f, 0.3f, 0.3f};

    float3 red = {1.0f, 0.0f, 0.0f};
    float3 green = {0.0f, 1.0f, 0.0f};
    float3 blue = {0.0f, 0.0f, 1.0f};
    float3 white = {1.0f, 1.0f, 1.0f};

    float3 v0 = {-1.0f, -1.0f, -1.0f};
    float3 v1 = {1.0f, -1.0f, -1.0f};
    float3 v2 = {1.0f, 1.0f, -1.0f};
    float3 v3 = {-1.0f, 1.0f, -1.0f};

    float3 v4 = {-1.0f, -1.0f, 1.0f};
    float3 v5 = {1.0f, -1.0f, 1.0f};
    float3 v6 = {1.0f, 1.0f, 1.0f};
    float3 v7 = {-1.0f, 1.0f, 1.0f};

    framebuffer.clear(gray);

    // transform.multiplyByScale({0.5f, 0.5f, 0.5f});

    // BACK (-Z)
    draw(framebuffer, transform, Point(v0, red), Point(v1, red), Point(v2, red));
    draw(framebuffer, transform, Point(v0, red), Point(v2, red), Point(v3, red));

    // FRONT (+Z)
    draw(framebuffer, transform, Point(v4, blue), Point(v6, blue), Point(v5, blue));
    draw(framebuffer, transform, Point(v4, blue), Point(v7, blue), Point(v6, blue));

    // LEFT (-X)
    draw(framebuffer, transform, Point(v0, green), Point(v3, green), Point(v7, green));
    draw(framebuffer, transform, Point(v0, green), Point(v7, green), Point(v4, green));

    // RIGHT (+X)
    draw(framebuffer, transform, Point(v1, white), Point(v5, white), Point(v6, white));
    draw(framebuffer, transform, Point(v1, white), Point(v6, white), Point(v2, white));

    // TOP (+Y)
    draw(framebuffer, transform, Point(v3, red), Point(v2, green), Point(v6, blue));
    draw(framebuffer, transform, Point(v3, red), Point(v6, blue), Point(v7, green));

    // BOTTOM (-Y)
    draw(framebuffer, transform, Point(v0, red), Point(v4, green), Point(v5, blue));
    draw(framebuffer, transform, Point(v0, red), Point(v5, blue), Point(v1, green));

    ImageExporter::saveTGA(framebuffer.getColorBuffer(), "output.tga");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms\n";

    return 0;
}
