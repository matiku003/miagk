#pragma once

#include "core/color.h"

/**
 * @brief Represents a 2D point with an associated color.
 */
struct Point {
    float x = 0.0f;
    float y = 0.0f;
    Color color{};
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
