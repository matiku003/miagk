#pragma once

#include <algorithm>

/**
 * @brief Represents a point in 2D.
 */
struct Point {
    float x = 0.0f;
    float y = 0.0f;
};

/**
 * @brief Represents a triangle in 2D. Points are in canonical coordinates [-1, 1].
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
inline AABB getTriangleAABB(const Triangle& triangle) {
    return {std::min({triangle.a.x, triangle.b.x, triangle.c.x}),
            std::min({triangle.a.y, triangle.b.y, triangle.c.y}),
            std::max({triangle.a.x, triangle.b.x, triangle.c.x}),
            std::max({triangle.a.y, triangle.b.y, triangle.c.y})};
}
