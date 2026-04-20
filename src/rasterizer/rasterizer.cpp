#include "rasterizer/rasterizer.h"

#include <algorithm>

#include "core/color.h"
#include "core/image.h"
#include "math/geometry.h"
#include "math/math.h"

bool Rasterizer::isInsideTriangle(const Triangle& triangle, const Point& point) {
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

bool Rasterizer::isFrontFacing(const Triangle& triangle) {
    float area = (triangle.b.x - triangle.a.x) * (triangle.c.y - triangle.a.y) -
                 (triangle.b.y - triangle.a.y) * (triangle.c.x - triangle.a.x);

    return area < 0;
}

Point Rasterizer::toImageSpace(const Point& point, const Image& image) {
    const float width = static_cast<float>(image.getWidth());
    const float height = static_cast<float>(image.getHeight());

    float x = (point.x + 1.0f) * width * 0.5f;
    float y = (point.y + 1.0f) * height * 0.5f;
    return {x, y, point.color};
}

Color Rasterizer::getInterpolatedColor(const Triangle& triangle, const Barycentric& barycentricCoords) {
    return (barycentricCoords.lambda1 * triangle.a.color) + (barycentricCoords.lambda2 * triangle.b.color) +
           (barycentricCoords.lambda3 * triangle.c.color);
}

AABB Rasterizer::clampAABBToImage(const AABB& bounds, const Image& img) {
    return {std::max(bounds.minX, 0.0f),
            std::max(bounds.minY, 0.0f),
            std::min(bounds.maxX, (float)img.getWidth() - 1),
            std::min(bounds.maxY, (float)img.getHeight() - 1)};
}

void Rasterizer::drawTriangle(Image& image, const Triangle& triangle) {
    Triangle triangleInImageSpace = {
        toImageSpace(triangle.a, image), toImageSpace(triangle.b, image), toImageSpace(triangle.c, image)};

    if (!isFrontFacing(triangleInImageSpace)) {
        return;
    }

    AABB bounds = getTriangleAABB(triangleInImageSpace);
    AABB clippedBounds = clampAABBToImage(bounds, image);

    unsigned int imageWidth = image.getWidth();
    unsigned int imageHeight = image.getHeight();

    for (int y = (int)clippedBounds.minY; y <= (int)clippedBounds.maxY; ++y) {
        for (int x = (int)clippedBounds.minX; x <= (int)clippedBounds.maxX; ++x) {
            Point point = {float(x), float(y)};

            if (isInsideTriangle(triangleInImageSpace, point)) {
                Barycentric barycentricCoords = getBarycentricCoordinates(triangleInImageSpace, point);
                Color interpolatedColor = getInterpolatedColor(triangleInImageSpace, barycentricCoords);

                unsigned int index = (y * imageWidth) + x;
                image.setPixelColor(index, interpolatedColor);
            }
        }
    }
}
