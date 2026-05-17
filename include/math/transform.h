#pragma once

#include <cmath>

#include "math.h"
#include "matrix.h"
#include "vector.h"

/**
 * @brief Basic transform system for 3D rendering pipeline.
 *
 * Stores and manages model, view, and projection matrices.
 * Used for simple MVP (Model-View-Projection) transformations.
 */
struct TransformSystem {
    static constexpr float PI = 3.1415926535f;

    float4x4 obj2world{};
    float4x4 world2view{};
    float4x4 view2proj{};

    /**
     * @brief Sets the view matrix using a look-at configuration.
     *
     * @param eye Camera position in world space.
     * @param center Target point the camera is looking at.
     * @param upVector Up direction vector.
     */
    void setLookAt(float3 eye, float3 center, float3 upVector) {
        float3 forward = normalize(center - eye);
        float3 right = normalize(cross(forward, upVector));
        float3 up = cross(right, forward);

        world2view[0] = float4(right[0], up[0], -forward[0], 0);
        world2view[1] = float4(right[1], up[1], -forward[1], 0);
        world2view[2] = float4(right[2], up[2], -forward[2], 0);
        world2view[3] = float4(-dot(right, eye), -dot(up, eye), dot(forward, eye), 1);
    }

    /**
     * @brief Sets the projection matrix.
     *
     * @param fovY Field of view in degrees (vertical axis).
     * @param aspect Aspect ratio (width / height).
     * @param near Near clipping plane distance.
     * @param far Far clipping plane distance.
     */
    void setPerspective(float fovY, float aspect, float near, float far) {
        fovY *= PI / 360;
        float f = std::cosf(fovY) / std::sinf(fovY);

        view2proj[0] = float4{f / aspect, 0.0f, 0.0f, 0.0f};
        view2proj[1] = float4{0.0f, f, 0.0f, 0.0f};
        view2proj[2] = float4{0.0f, 0.0f, (far + near) / (far - near), -1.0f};
        view2proj[3] = float4{0.0f, 0.0f, (2 * far * near) / (far - near), 0.0f};
    }

    /**
     * @brief Applies a translation to the model matrix.
     *
     * @param v Translation vector.
     */
    void multiplyByTranslation(float3 v) {
        float4x4 translationMatrix(
            float4(1, 0, 0, 0), float4(0, 1, 0, 0), float4(0, 0, 1, 0), float4(v.x, v.y, v.z, 1));
        obj2world = translationMatrix * obj2world;
    }

    /**
     * @brief Applies a scale transformation to the model matrix.
     *
     * @param v Scale factors for x, y, and z axes.
     */
    void multiplyByScale(float3 v) {
        float4x4 scaleMatrix(float4(v.x, 0, 0, 0), float4(0, v.y, 0, 0), float4(0, 0, v.z, 0), float4(0, 0, 0, 1));
        obj2world = scaleMatrix * obj2world;
    }

    /**
     * @brief Applies a rotation to the model matrix.
     *
     * @param a Rotation angle in degrees.
     * @param v Rotation axis.
     */
    void multiplyByRotation(float a, float3 v) {
        float s = sinf(a * PI / 180);
        float c = cosf(a * PI / 180);
        v = normalize(v);
        float4x4 rotationMatrix(
            float4(v.x * v.x * (1 - c) + c, v.y * v.x * (1 - c) + v.z * s, v.x * v.z * (1 - c) - v.y * s, 0),
            float4(v.x * v.y * (1 - c) - v.z * s, v.y * v.y * (1 - c) + c, v.y * v.z * (1 - c) + v.x * s, 0),
            float4(v.x * v.z * (1 - c) + v.y * s, v.y * v.z * (1 - c) - v.x * s, v.z * v.z * (1 - c) + c, 0),
            float4(0, 0, 0, 1));
        obj2world = rotationMatrix * obj2world;
    }
};
