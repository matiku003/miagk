#pragma once

#include "light.h"

class PointLight : public Light {
  public:
    float3 calculate(const TransformSystem& transform, const Fragment& fragment) override;
};
