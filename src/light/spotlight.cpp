#include "light/spotlight.h"

#include <algorithm>
#include <cmath>

#include "math/math.h"
#include "math/matrix.h"
#include "math/transform.h"
#include "math/vector.h"
#include "rasterizer/fragment.h"

float3 Spotlight::calculate(const TransformSystem& transform, const Fragment& fragment) {
    float4x4 modelView = transform.world2view * transform.obj2world;

    float4 n4 = modelView * float4(fragment.normal.x, fragment.normal.y, fragment.normal.z, 0.0f);
    float3 N = normalize(float3(n4.x, n4.y, n4.z));

    float4 p4 = modelView * float4(fragment.position.x, fragment.position.y, fragment.position.z, 1.0f);
    float3 fragPosView = float3(p4.x, p4.y, p4.z);

    float4 lp4 = transform.world2view * float4(this->position.x, this->position.y, this->position.z, 1.0f);
    float3 lightPosView = float3(lp4.x, lp4.y, lp4.z);

    float4 ld4 = transform.world2view * float4(this->direction.x, this->direction.y, this->direction.z, 0.0f);
    float3 lightDirView = normalize(float3(ld4.x, ld4.y, ld4.z));

    float3 L = normalize(lightPosView - fragPosView);
    float3 V = normalize(-fragPosView);

    float3 lightToFrag = -L;

    float theta = dot(lightToFrag, lightDirView);

    float epsilon = this->cutoff - this->outerCutoff;
    float spotIntensity = std::max(0.0f, std::min(1.0f, (theta - this->outerCutoff) / epsilon));

    float distance = length(lightPosView - fragPosView);
    float attenuation = 1.0f / (this->constant + this->linear * distance + this->quadratic * (distance * distance));

    float3 ambientPart = this->ambient;

    float diffCoeff = std::max(dot(L, N), 0.0f);
    float3 diffusePart = this->diffuse * diffCoeff;

    float3 R = reflect(-L, N);
    float specCoeff = std::pow(std::max(dot(R, V), 0.0f), this->shininess);
    float3 specularPart = this->specular * specCoeff;

    return ambientPart + (diffusePart + specularPart) * spotIntensity * attenuation;
}
