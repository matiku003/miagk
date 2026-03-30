#pragma once

/**
 * @brief Represents a point in 2D.
 */
struct Point {
    float x = 0;
    float y = 0;
};

/**
 * @brief Represents a triangle in 2D. Points are in canonical coordinates [-1, 1].
 *
 * @note Winding order of the vertices must be counterclockwise.
 */
struct Triangle {
    Point a = {0, 0};
    Point b = {0, 0};
    Point c = {0, 0};
};
