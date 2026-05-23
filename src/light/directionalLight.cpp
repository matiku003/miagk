#include "light/directionalLight.h"

#include <algorithm>
#include <cmath>

#include "math/math.h"
#include "math/matrix.h"
#include "math/transform.h"
#include "math/vector.h"
#include "rasterizer/fragment.h"

float3 DirectionalLight::calculate(const TransformSystem& transform, const Fragment& fragment) {
    float4x4 modelView = transform.world2view * transform.obj2world;

    float4 n4 = modelView * float4(fragment.normal.x, fragment.normal.y, fragment.normal.z, 0.0f);
    float3 N = normalize(float3(n4.x, n4.y, n4.z));

    float4 p4 = modelView * float4(fragment.position.x, fragment.position.y, fragment.position.z, 1.0f);
    float3 posView = float3(p4.x, p4.y, p4.z);
    float3 V = normalize(-posView);

    float4 l4 = transform.world2view * float4(this->position.x, this->position.y, this->position.z, 0.0f);
    float3 L = normalize(-float3(l4.x, l4.y, l4.z));

    float3 R = reflect(-L, N);

    float diffCoeff = std::max(dot(L, N), 0.0f);
    float3 diffusePart = this->diffuse * diffCoeff;

    float specCoeff = std::pow(std::max(dot(R, V), 0.0f), this->shininess);
    float3 specularPart = this->specular * specCoeff;

    return this->ambient + diffusePart + specularPart;
}
