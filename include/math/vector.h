#pragma once

#include <cmath>

/**
 * @brief Represents a 3D vector used for positions, directions or colors.
 */
struct float3 {
    union {
        struct {
            float x, y, z;
        };
        struct {
            float r, g, b;
        };
        float data[3];
    };

    static constexpr float epsilon = 0.0001f;

    constexpr float3() : x(0.0f), y(0.0f), z(0.0f) {}
    constexpr float3(float x, float y, float z) : x(x), y(y), z(z) {}

    float& operator[](size_t index) {
        return data[index];
    }

    const float& operator[](size_t index) const {
        return data[index];
    }

    float3 operator-() const {
        return {-x, -y, -z};
    }

    float3 operator+(const float3& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    float3 operator-(const float3& v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    float3& operator+=(const float3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    float3 operator*(float s) const {
        return {x * s, y * s, z * s};
    }

    float3 operator*(const float3& v) const {
        return {x * v.x, y * v.y, z * v.z};
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    float3 normalized() const {
        float len = length();
        if (len > epsilon) {
            float inv = 1.0f / len;
            return {x * inv, y * inv, z * inv};
        }
        return {0.0f, 0.0f, 0.0f};
    }
};

inline float3 operator*(float s, const float3& v) {
    return v * s;
}

/**
 * @brief Represents a 4D vector used for matrix4x4 manipulation.
 */
struct float4 {
    union {
        struct {
            float x, y, z, w;
        };
        struct {
            float r, g, b, a;
        };
        float data[4];
    };

    constexpr float4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    constexpr float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    constexpr float4(float3 v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

    float& operator[](size_t index) {
        return data[index];
    }

    const float& operator[](size_t index) const {
        return data[index];
    }
};

/**
 * @brief Represents a 3D integer vector used for indexing triangles.
 */
struct int3 {
    union {
        struct {
            int x, y, z;
        };
        int data[3];
    };

    constexpr int3() : x(0), y(0), z(0) {}
    constexpr int3(int x, int y, int z) : x(x), y(y), z(z) {}

    int& operator[](size_t index) {
        return data[index];
    }

    const int& operator[](size_t index) const {
        return data[index];
    }
};
