#pragma once

#include <algorithm>

#include "math/geometry.h"

/**
 * @brief Represents a 2D axis-aligned bounding box.
 */
struct AABB {
    float minX, minY;
    float maxX, maxY;
};

/**
 * @brief Computes axis-aligned bounding box for a triangle.
 *
 * @param triangle Input triangle in 2D space.
 * @return AABB enclosing all three triangle vertices.
 */
[[nodiscard]] constexpr AABB getTriangleAABB(const Triangle& triangle) {
    return {std::min({triangle.a.x, triangle.b.x, triangle.c.x}),
            std::min({triangle.a.y, triangle.b.y, triangle.c.y}),
            std::max({triangle.a.x, triangle.b.x, triangle.c.x}),
            std::max({triangle.a.y, triangle.b.y, triangle.c.y})};
}

/**
 * @brief Represents barycentric coordinates of a point relative to a triangle.
 *
 * The values (lambda1, lambda2, lambda3) correspond to vertices (a, b, c).
 */
struct Barycentric {
    float lambda1, lambda2, lambda3;
};

/**
 * @brief Computes barycentric coordinates of a point with respect to a triangle.
 *
 * @param t Input triangle in 2D space.
 * @param p Point to transform into barycentric coordinates.
 * @return Barycentric weights for triangle vertices.
 */
[[nodiscard]] constexpr Barycentric getBarycentricCoordinates(const Triangle& t, const Point& p) {
    float lambda1 = (((t.b.y - t.c.y) * (p.x - t.c.x)) + ((t.c.x - t.b.x) * (p.y - t.c.y))) /
                    (((t.b.y - t.c.y) * (t.a.x - t.c.x)) + ((t.c.x - t.b.x) * (t.a.y - t.c.y)));
    float lambda2 = (((t.c.y - t.a.y) * (p.x - t.c.x)) + ((t.a.x - t.c.x) * (p.y - t.c.y))) /
                    (((t.c.y - t.a.y) * (t.b.x - t.c.x)) + ((t.a.x - t.c.x) * (t.b.y - t.c.y)));
    float lambda3 = 1.0f - lambda1 - lambda2;

    return {lambda1, lambda2, lambda3};
}
