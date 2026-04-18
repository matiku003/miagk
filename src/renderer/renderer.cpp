#include "renderer/renderer.h"

#include "core/color.h"
#include "core/image.h"
#include "math/geometry.h"

bool Renderer::isInsideTriangle(const Triangle& triangle, const Point& point) {
    bool halfSpace1 = ((triangle.a.x - triangle.b.x) * (point.y - triangle.a.y)) -
                          ((triangle.a.y - triangle.b.y) * (point.x - triangle.a.x)) >
                      0;

    bool halfSpace2 = ((triangle.b.x - triangle.c.x) * (point.y - triangle.b.y)) -
                          ((triangle.b.y - triangle.c.y) * (point.x - triangle.b.x)) >
                      0;

    bool halfSpace3 = ((triangle.c.x - triangle.a.x) * (point.y - triangle.c.y)) -
                          ((triangle.c.y - triangle.a.y) * (point.x - triangle.c.x)) >
                      0;

    return halfSpace1 && halfSpace2 && halfSpace3;
}

Point Renderer::toImageSpace(const Point& point, const Image& image) {
    const float width = static_cast<float>(image.width);
    const float height = static_cast<float>(image.height);

    float x = (point.x + 1.0f) * width * 0.5f;
    float y = (1.0f - point.y) * height * 0.5f;
    return {x, y};
}

void Renderer::drawTriangle(Image& image, const Triangle& triangle, const Color& color) {
    Triangle triangleInImageSpace = {
        toImageSpace(triangle.a, image), toImageSpace(triangle.b, image), toImageSpace(triangle.c, image)};

    for (size_t y = 0; y < image.height; ++y) {
        for (size_t x = 0; x < image.width; ++x) {
            Point point = {float(x), float(y)};

            if (isInsideTriangle(triangleInImageSpace, point)) {
                size_t index = (y * image.width) + x;
                image.colorBuffer[index] = color;
            }
        }
    }
}
