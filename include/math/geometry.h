#pragma once

#include <algorithm>

#include "math/vector.h"

/**
 * @brief Represents a 3D point with an associated color.
 */
struct Point {
    float3 position{};
    float3 color{};
};

/**
 * @brief Represents a triangle in 3D. Points are in canonical coordinates [-1, 1].
 *
 * @note Winding order of the vertices must be clockwise.
 */
struct Triangle {
    Point a{};
    Point b{};
    Point c{};
};

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
    return {std::min({triangle.a.position.x, triangle.b.position.x, triangle.c.position.x}),
            std::min({triangle.a.position.y, triangle.b.position.y, triangle.c.position.y}),
            std::max({triangle.a.position.x, triangle.b.position.x, triangle.c.position.x}),
            std::max({triangle.a.position.y, triangle.b.position.y, triangle.c.position.y})};
}
