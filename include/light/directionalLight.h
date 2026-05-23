#pragma once

#include "light.h"
#include "math/transform.h"
#include "math/vector.h"
#include "rasterizer/fragment.h"

class DirectionalLight : public Light {
  public:
    float3 calculate(const TransformSystem& transform, const Fragment& fragment) override;
};
