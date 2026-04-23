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
