#include "rasterizer/rasterizer.h"

#include <algorithm>

#include "core/framebuffer.h"
#include "math/barycentric.h"
#include "math/geometry.h"
#include "math/vector.h"

bool Rasterizer::isInsideTriangle(const PreparedTriangle& triangle, const Point& point) {
    float edgeAB = (triangle.dx12 * (point.position.y - triangle.a.position.y)) -
                   (triangle.dy12 * (point.position.x - triangle.a.position.x));
    float edgeBC = (triangle.dx23 * (point.position.y - triangle.b.position.y)) -
                   (triangle.dy23 * (point.position.x - triangle.b.position.x));
    float edgeCA = (triangle.dx31 * (point.position.y - triangle.c.position.y)) -
                   (triangle.dy31 * (point.position.x - triangle.c.position.x));

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

Point Rasterizer::toImageSpace(const Point& point, const Framebuffer& buffer) {
    const float width = static_cast<float>(buffer.getWidth());
    const float height = static_cast<float>(buffer.getHeight());

    float x = (point.position.x + 1.0f) * width * 0.5f;
    float y = (point.position.y + 1.0f) * height * 0.5f;
    float z = point.position.z;

    return {
        {x, y, z},
        point.color
    };
}

Barycentric Rasterizer::getBarycentricCoordinates(const PreparedTriangle& triangle, const Point& point) {
    float e2 = (triangle.dy23 * (point.position.x - triangle.c.position.x)) +
               ((-triangle.dx23) * (point.position.y - triangle.c.position.y));
    float e3 = (triangle.dy31 * (point.position.x - triangle.c.position.x)) +
               ((-triangle.dx31) * (point.position.y - triangle.c.position.y));

    float l1 = e2 * triangle.inverseDenominator;
    float l2 = e3 * triangle.inverseDenominator;
    return {l1, l2, 1.0f - l1 - l2};
}

AABB Rasterizer::clampAABBToImage(const AABB& bounds, const Framebuffer& buffer) {
    return {std::max(bounds.minX, 0.0f),
            std::max(bounds.minY, 0.0f),
            std::min(bounds.maxX, (float)buffer.getWidth() - 1),
            std::min(bounds.maxY, (float)buffer.getHeight() - 1)};
}

void Rasterizer::drawTriangle(Framebuffer& buffer, const Triangle& triangle) {
    Triangle triangleInImageSpace = {
        toImageSpace(triangle.a, buffer), toImageSpace(triangle.b, buffer), toImageSpace(triangle.c, buffer)};

    PreparedTriangle preparedTriangle(triangleInImageSpace);

    if (!isFrontFacing(preparedTriangle)) {
        return;
    }

    AABB bounds = getTriangleAABB(triangleInImageSpace);
    AABB clippedBounds = clampAABBToImage(bounds, buffer);

    unsigned int imageWidth = buffer.getWidth();
    unsigned int imageHeight = buffer.getHeight();

    for (int y = (int)clippedBounds.minY; y <= (int)clippedBounds.maxY; ++y) {
        for (int x = (int)clippedBounds.minX; x <= (int)clippedBounds.maxX; ++x) {
            Point point = {
                {x + 0.5f, y + 0.5f, 0.0f},
                {}
            };

            if (isInsideTriangle(preparedTriangle, point)) {
                Barycentric barycentricCoords = getBarycentricCoordinates(preparedTriangle, point);
                float3 interpolatedColor = interpolate(barycentricCoords,
                                                       triangleInImageSpace.a.color,
                                                       triangleInImageSpace.b.color,
                                                       triangleInImageSpace.c.color);
                float depth = interpolate(barycentricCoords,
                                          triangleInImageSpace.a.position.z,
                                          triangleInImageSpace.b.position.z,
                                          triangleInImageSpace.c.position.z);

                unsigned int index = (y * imageWidth) + x;
                if (buffer.passesDepthTest(index, depth)) {
                    buffer.setPixel(index, depth, interpolatedColor);
                }
            }
        }
    }
}
