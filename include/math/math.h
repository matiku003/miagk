#pragma once

#include <algorithm>
#include <cmath>

#include "matrix.h"
#include "vector.h"

/**
 * @brief Computes dot product of two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return Scalar dot product.
 */
inline float dot(const float3& a, const float3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * @brief Computes dot product of two 4D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return Scalar dot product.
 */
inline float dot(const float4& a, const float4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**
 * @brief Computes cross product of two 3D vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return Vector perpendicular to both inputs.
 */
inline float3 cross(const float3& a, const float3& b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

/**
 * @brief Computes length (magnitude) of a 3D vector.
 *
 * @param v Input vector.
 * @return Length of vector.
 */
inline float length(const float3& v) {
    return std::sqrt(dot(v, v));
}

/**
 * @brief Normalizes a 3D vector to unit length.
 *
 * @param v Input vector.
 * @return Normalized vector.
 */
inline float3 normalize(const float3& v) {
    float len = length(v);
    if (len > float3::epsilon) {
        float inv = 1.0f / len;
        return {v.x * inv, v.y * inv, v.z * inv};
    }
    return {0.0f, 0.0f, 0.0f};
}

/**
 * @brief Reflects vector v around normal n.
 *
 * @param v Incoming vector.
 * @param n Normal vector (assumed normalized).
 * @return Reflected vector.
 */
inline float3 reflect(const float3& v, const float3& n) {
    return v - 2.0f * dot(v, n) * n;
}

/**
 * @brief Clamps scalar value to [0, 1] range.
 *
 * @param x Input value.
 * @return Clamped value.
 */
inline float saturate(float x) {
    return std::clamp(x, 0.0f, 1.0f);
}

/**
 * @brief Clamps each component of a vector to [0, 1].
 *
 * @param v Input vector.
 * @return Clamped vector.
 */
inline float3 saturate(const float3& v) {
    return {std::clamp(v.x, 0.0f, 1.0f), std::clamp(v.y, 0.0f, 1.0f), std::clamp(v.z, 0.0f, 1.0f)};
}

/**
 * @brief Multiplies two 4x4 matrices.
 *
 * Column-major convention.
 *
 * @param a Left matrix.
 * @param b Right matrix.
 * @return Result of multiplication (a * b).
 */
inline float4x4 operator*(const float4x4& a, const float4x4& b) {
    float4x4 r;

    for (size_t col = 0; col < 4; ++col) {
        for (size_t row = 0; row < 4; ++row) {
            r[col][row] = a[0][row] * b[col][0] + a[1][row] * b[col][1] + a[2][row] * b[col][2] + a[3][row] * b[col][3];
        }
    }

    return r;
}

/**
 * @brief Multiplies a 4x4 matrix by a 4D column vector.
 *
 * @param m Matrix.
 * @param v Vector.
 * @return Transformed vector.
 */
inline float4 operator*(const float4x4& m, const float4& v) {
    return {m[0].x * v.x + m[1].x * v.y + m[2].x * v.z + m[3].x * v.w,
            m[0].y * v.x + m[1].y * v.y + m[2].y * v.z + m[3].y * v.w,
            m[0].z * v.x + m[1].z * v.y + m[2].z * v.z + m[3].z * v.w,
            m[0].w * v.x + m[1].w * v.y + m[2].w * v.z + m[3].w * v.w};
}

/**
 * @brief Multiplies a 4x4 matrix by a 3D column vector (assumes w = 1).
 *
 * @param m Matrix.
 * @param v 3D vector.
 * @return Transformed 4D vector.
 */
inline float4 operator*(const float4x4& m, const float3& v) {
    return m * float4{v.x, v.y, v.z, 1.0f};
}

/**
 * @brief Transposes a 4x4 matrix.
 *
 * Rows become columns and vice versa.
 *
 * @param m Input matrix.
 * @return Transposed matrix.
 */
inline float4x4 transpose(const float4x4& m) {
    float4x4 r;

    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            r[i][j] = m[j][i];

    return r;
}
