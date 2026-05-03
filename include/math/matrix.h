#pragma once

#include "vector.h"

/**
 * @brief Represents a 4x4 matrix used for 3D transformations.
 */
struct float4x4 {
    float4 columns[4];

    constexpr float4x4()
        : columns{
              float4{1, 0, 0, 0},
              float4{0, 1, 0, 0},
              float4{0, 0, 1, 0},
              float4{0, 0, 0, 1}
    } {}

    constexpr float4x4(const float4& c0, const float4& c1, const float4& c2, const float4& c3)
        : columns{c0, c1, c2, c3} {}

    float4& operator[](size_t i) {
        return columns[i];
    }

    const float4& operator[](size_t i) const {
        return columns[i];
    }
};
