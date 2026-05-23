#pragma once

#include "math/transform.h"
#include "math/vector.h"
#include "rasterizer/fragment.h"

class Light {
  public:
    float3 position;
    float3 ambient;
    float3 diffuse;
    float3 specular;
    float shininess = 32.0f;

    virtual ~Light() = default;

    /**
     * @brief Computes the lighting contribution for a specific surface fragment.
     *
     * @param transform The transformation system used to convert coordinates between
     *                  different spaces (Model, World, and View space).
     * @param fragment  The surface fragment data containing the position and
     *                  normal vector of the point being shaded.
     * @return The calculated RGB color intensity contribution from this light source.
     */
    virtual float3 calculate(const TransformSystem& transform, const Fragment& fragment) = 0;
};
