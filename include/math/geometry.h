#pragma once

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
 * @note Winding order of the vertices must be counterclockwise.
 */
struct Triangle {
    Point a{};
    Point b{};
    Point c{};
};
