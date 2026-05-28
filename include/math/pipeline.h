#pragma once

#include "geometry.h"
#include "transform.h"
#include "vector.h"

/**
 * @brief Applies Model-View-Projection transformation to a point.
 */
inline Point applyMVP(const TransformSystem& t, const Point& p) {
    float4 v = {p.position.x, p.position.y, p.position.z, 1.0f};

    float4 world = t.obj2world * v;
    float4 view = t.world2view * world;
    float4 proj = t.view2proj * view;

    proj.x /= proj.w;
    proj.y /= proj.w;
    proj.z /= proj.w;

    float4 n4 = t.obj2world * float4{p.normal.x, p.normal.y, p.normal.z, 0.0f};
    float3 normal = {n4.x, n4.y, n4.z};
    normalize(normal);

    return {
        { proj.x,  proj.y,  proj.z},
        p.color, normal, {world.x, world.y, world.z}
    };
}
