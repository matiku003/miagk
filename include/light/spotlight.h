#pragma once

#include <cmath>

#include "light.h"
#include "math/transform.h"
#include "math/vector.h"
#include "rasterizer/fragment.h"

class Spotlight : public Light {
  public:
    float3 direction;
    float cutoff = std::cos(15.0f * 3.14159f / 180.0f);
    float outerCutoff = std::cos(20.0f * 3.14159f / 180.0f);
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    float3 calculate(const TransformSystem& transform, const Fragment& fragment) override;
};
