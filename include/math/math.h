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
 * @brief Performs barycentric interpolation of a value inside a triangle.
 *
 * @tparam T Type of interpolated attribute (e.g. float, Color).
 * @param b Barycentric coordinates of the sample point.
 * @param a Value at vertex A.
 * @param c Value at vertex B.
 * @param d Value at vertex C.
 * @return Interpolated value at the given point.
 */
template <typename T> T interpolate(const Barycentric& b, const T& a, const T& c, const T& d) {
    return b.lambda1 * a + b.lambda2 * c + b.lambda3 * d;
}
