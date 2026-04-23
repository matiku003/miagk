#include "rasterizer/rasterizer.h"

#include <algorithm>

#include "core/color.h"
#include "core/image.h"
#include "math/geometry.h"
#include "math/math.h"

bool Rasterizer::isInsideTriangle(const PreparedTriangle& triangle, const Point& point) {
    float edgeAB = (triangle.dx12 * (point.y - triangle.a.y)) - (triangle.dy12 * (point.x - triangle.a.x));
    float edgeBC = (triangle.dx23 * (point.y - triangle.b.y)) - (triangle.dy23 * (point.x - triangle.b.x));
    float edgeCA = (triangle.dx31 * (point.y - triangle.c.y)) - (triangle.dy31 * (point.x - triangle.c.x));

    bool halfSpace1 =
        (triangle.dy12 < 0 || (triangle.dy12 == 0 && triangle.dx12 > 0)) ? (edgeAB >= 0.0f) : (edgeAB > 0.0f);
    bool halfSpace2 =
        (triangle.dy23 < 0 || (triangle.dy23 == 0 && triangle.dx23 > 0)) ? (edgeBC >= 0.0f) : (edgeBC > 0.0f);
    bool halfSpace3 =
        (triangle.dy31 < 0 || (triangle.dy31 == 0 && triangle.dx31 > 0)) ? (edgeCA >= 0.0f) : (edgeCA > 0.0f);

    return halfSpace1 && halfSpace2 && halfSpace3;
}

bool Rasterizer::isFrontFacing(const PreparedTriangle& triangle) {
    float area = ((-triangle.dx12) * (triangle.dy31)) - ((-triangle.dy12) * (triangle.dx31));

    return area < 0;
}

Point Rasterizer::toImageSpace(const Point& point, const Image& image) {
    const float width = static_cast<float>(image.getWidth());
    const float height = static_cast<float>(image.getHeight());

    float x = (point.x + 1.0f) * width * 0.5f;
    float y = (point.y + 1.0f) * height * 0.5f;
    return {x, y, point.color};
}

Barycentric Rasterizer::getBarycentricCoordinates(const PreparedTriangle& triangle, const Point& point) {
    float e2 = (triangle.dy23 * (point.x - triangle.c.x)) + ((-triangle.dx23) * (point.y - triangle.c.y));
    float e3 = (triangle.dy31 * (point.x - triangle.c.x)) + ((-triangle.dx31) * (point.y - triangle.c.y));

    float l1 = e2 * triangle.inverseDenominator;
    float l2 = e3 * triangle.inverseDenominator;
    return {l1, l2, 1.0f - l1 - l2};
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

    PreparedTriangle preparedTriangle(triangleInImageSpace);

    if (!isFrontFacing(preparedTriangle)) {
        return;
    }

    AABB bounds = getTriangleAABB(triangleInImageSpace);
    AABB clippedBounds = clampAABBToImage(bounds, image);

    unsigned int imageWidth = image.getWidth();
    unsigned int imageHeight = image.getHeight();

    for (int y = (int)clippedBounds.minY; y <= (int)clippedBounds.maxY; ++y) {
        for (int x = (int)clippedBounds.minX; x <= (int)clippedBounds.maxX; ++x) {
            Point point = {x + 0.5f, y + 0.5f};

            if (isInsideTriangle(preparedTriangle, point)) {
                Barycentric barycentricCoords = getBarycentricCoordinates(preparedTriangle, point);
                Color interpolatedColor = getInterpolatedColor(triangleInImageSpace, barycentricCoords);

                unsigned int index = (y * imageWidth) + x;
                image.setPixelColor(index, interpolatedColor);
            }
        }
    }
}
