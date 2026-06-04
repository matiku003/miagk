#include "mesh/mesh.h"

#include <cmath>
#include <vector>

#include "math/geometry.h"
#include "math/math.h"
#include "math/vector.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Mesh::buildTriangle() {
    vertices.resize(3);
    indices.resize(1);
    vertices[0].position = float3(-0.5f, 0.0f, 0.0f);
    vertices[1].position = float3(0.0f, 0.5f, 0.0f);
    vertices[2].position = float3(0.5f, 0.0f, 0.0f);
    indices[0] = int3(0, 1, 2);
}

void Mesh::buildCube() {
    vertices.resize(24);
    indices.resize(12 * 3);

    float s = 0.5f;

    auto addFace = [&](int i, float3 a, float3 b, float3 c, float3 d) {
        int start = i * 4;

        vertices[start + 0].position = a;
        vertices[start + 1].position = b;
        vertices[start + 2].position = c;
        vertices[start + 3].position = d;

        int triStart = i * 6;

        indices[triStart + 0] = int3(start + 0, start + 2, start + 1);
        indices[triStart + 1] = int3(start + 2, start + 3, start + 1);
    };

    addFace(0, float3(-s, -s, s), float3(s, -s, s), float3(-s, s, s), float3(s, s, s));
    addFace(1, float3(s, -s, -s), float3(-s, -s, -s), float3(s, s, -s), float3(-s, s, -s));
    addFace(2, float3(-s, -s, -s), float3(-s, -s, s), float3(-s, s, -s), float3(-s, s, s));
    addFace(3, float3(s, -s, s), float3(s, -s, -s), float3(s, s, s), float3(s, s, -s));
    addFace(4, float3(-s, s, s), float3(s, s, s), float3(-s, s, -s), float3(s, s, -s));
    addFace(5, float3(-s, -s, -s), float3(s, -s, -s), float3(-s, -s, s), float3(s, -s, s));
}

void Mesh::buildPyramid() {
    vertices.resize(5);
    indices.resize(6);

    vertices[0].position = float3(-0.5f, -0.5f, -0.5f);
    vertices[1].position = float3(-0.5f, -0.5f, 0.5f);
    vertices[2].position = float3(0.5f, -0.5f, 0.5f);
    vertices[3].position = float3(0.5f, -0.5f, -0.5f);
    vertices[4].position = float3(0.0f, 0.5f, 0.0f);

    // base
    indices[0] = int3(0, 1, 2);
    indices[1] = int3(0, 2, 3);

    // sides
    indices[2] = int3(0, 4, 1);
    indices[3] = int3(1, 4, 2);
    indices[4] = int3(2, 4, 3);
    indices[5] = int3(3, 4, 0);
}

void Mesh::buildTetrahedron() {
    vertices.resize(4);
    indices.resize(4);

    vertices[0].position = float3(0.0f, 0.5f, 0.0f);
    vertices[1].position = float3(-0.5f, -0.5f, 0.5f);
    vertices[2].position = float3(0.5f, -0.5f, 0.5f);
    vertices[3].position = float3(0.0f, -0.5f, -0.5f);

    indices[0] = int3(0, 2, 1);
    indices[1] = int3(0, 3, 2);
    indices[2] = int3(0, 1, 3);
    indices[3] = int3(1, 2, 3);
}

void Mesh::buildCone(int step) {
    if (step < 3) {
        return;
    }

    float twoPI = 2.0f * 3.14159265f;
    float angleStep = twoPI / step;
    float radius = 0.5f;

    int sideRingStart = 0;
    int baseRingStart = step;

    int apex = step * 2;
    int baseCenter = step * 2 + 1;

    vertices.resize(step * 2 + 2);
    indices.resize(step * 2);

    for (int i = 0; i < step; i++) {
        float t = i * angleStep;

        float x = radius * std::cos(t);
        float z = radius * std::sin(t);

        vertices[sideRingStart + i].position = float3(x, -0.5f, z);
    }

    for (int i = 0; i < step; i++) {
        float t = i * angleStep;

        float x = radius * std::cos(t);
        float z = radius * std::sin(t);

        vertices[baseRingStart + i].position = float3(x, -0.5f, z);
    }

    vertices[apex].position = float3(0.0f, 0.5f, 0.0f);

    vertices[baseCenter].position = float3(0.0f, -0.5f, 0.0f);

    int indexCounter = 0;

    for (int i = 0; i < step; i++) {
        int next = (i + 1) % step;

        indices[indexCounter++] = int3(baseRingStart + i, baseCenter, baseRingStart + next);
        indices[indexCounter++] = int3(sideRingStart + i, sideRingStart + next, apex);
    }
}

void Mesh::buildCylinder(int verticalStep, int horizontalStep) {
    if (verticalStep < 3 || horizontalStep < 2)
        return;

    const float twoPI = 2.0f * 3.14159265f;
    const float angleStep = twoPI / verticalStep;
    const float radius = 0.5f;

    int rings = horizontalStep + 1;

    int sideVertexCount = rings * verticalStep;

    int baseCenterIndex = sideVertexCount;
    int topCenterIndex = sideVertexCount + 1;

    int vertexCount = sideVertexCount + 2;

    int sideTris = horizontalStep * verticalStep * 2;
    int capTris = verticalStep * 2;
    int indicesCount = sideTris + capTris;

    vertices.resize(vertexCount);
    indices.resize(indicesCount);

    for (int i = 0; i < rings; i++) {
        float y = -0.5f + (float(i) / horizontalStep);

        for (int j = 0; j < verticalStep; j++) {
            float t = -j * angleStep;

            float x = radius * std::cos(t);
            float z = radius * std::sin(t);

            vertices[i * verticalStep + j].position = float3(x, y, z);
        }
    }

    vertices[baseCenterIndex].position = float3(0.0f, -0.5f, 0.0f);
    vertices[topCenterIndex].position = float3(0.0f, 0.5f, 0.0f);

    int idx = 0;

    for (int i = 0; i < horizontalStep; i++) {
        for (int j = 0; j < verticalStep; j++) {
            int next = (j + 1) % verticalStep;

            int a = i * verticalStep + j;
            int b = (i + 1) * verticalStep + j;
            int c = i * verticalStep + next;
            int d = (i + 1) * verticalStep + next;

            indices[idx++] = int3(a, b, c);
            indices[idx++] = int3(c, b, d);
        }
    }

    for (int j = 0; j < verticalStep; j++) {
        int next = (j + 1) % verticalStep;

        indices[idx++] = int3(baseCenterIndex, j, next);
    }

    int topRingStart = (rings - 1) * verticalStep;

    for (int j = 0; j < verticalStep; j++) {
        int next = (j + 1) % verticalStep;

        indices[idx++] = int3(topCenterIndex, topRingStart + next, topRingStart + j);
    }
}

void Mesh::buildSphere(int verticalStep, int horizontalStep) {
    if (verticalStep < 3 || horizontalStep < 2)
        return;

    const int rings = horizontalStep + 2;

    const int vertexCount = verticalStep * rings;
    const int triangleCount = 2 * verticalStep * horizontalStep;

    vertices.resize(vertexCount);
    indices.resize(triangleCount);

    for (int y = 0; y < rings; ++y) {
        float ty = static_cast<float>(y) / (rings - 1);
        float angleY = ty * 3.14159265f;

        float py = std::cos(angleY);
        float radius = std::sqrt(1.0f - py * py);

        for (int x = 0; x < verticalStep; ++x) {
            float angleX = (2.0f * 3.14159265f * x) / verticalStep;

            float px = radius * std::cos(angleX);
            float pz = radius * std::sin(angleX);

            int index = x + y * verticalStep;
            vertices[index].position = float3(px * 0.5f, py * 0.5f, pz * 0.5f);
        }
    }

    for (int y = 0; y < horizontalStep; ++y) {
        for (int x = 0; x < verticalStep; ++x) {
            indices[x + 2 * y * verticalStep] = {(x + 1) % verticalStep + y * verticalStep,
                                                 x + verticalStep + y * verticalStep,
                                                 (x + 1) % verticalStep + verticalStep + y * verticalStep};
            indices[x + verticalStep + 2 * y * verticalStep] = {x + verticalStep + y * verticalStep,
                                                                x + 2 * verticalStep + y * verticalStep,
                                                                (x + 1) % verticalStep + verticalStep +
                                                                    y * verticalStep};
        }
    }
}

void Mesh::buildTorus(int verticalStep, int horizontalStep) {
    if (verticalStep < 3 || horizontalStep < 2)
        return;

    float R = 0.4f;
    float r = 0.1f;
    float PI = 3.14159265f;

    int vertexCount = verticalStep * horizontalStep;
    int triangleCount = verticalStep * horizontalStep * 2;

    vertices.resize(vertexCount);
    indices.resize(triangleCount);

    for (int i = 0; i < horizontalStep; i++) {
        float theta = (float)i * 2.0f * PI / horizontalStep;
        float cosTheta = std::cos(theta);
        float sinTheta = std::sin(theta);

        for (int j = 0; j < verticalStep; j++) {
            float phi = (float)j * 2.0f * PI / verticalStep;
            float cosPhi = std::cos(phi);
            float sinPhi = std::sin(phi);

            float x = (R + r * cosPhi) * cosTheta;
            float y = r * sinPhi;
            float z = (R + r * cosPhi) * sinTheta;

            vertices[i * verticalStep + j].position = float3(x, y, z);
        }
    }

    int idx = 0;
    for (int i = 0; i < horizontalStep; i++) {
        for (int j = 0; j < verticalStep; j++) {
            int current = i * verticalStep + j;
            int nextH = ((i + 1) % horizontalStep) * verticalStep + j;
            int nextV = i * verticalStep + ((j + 1) % verticalStep);
            int nextHV = ((i + 1) % horizontalStep) * verticalStep + ((j + 1) % verticalStep);

            indices[idx++] = int3(current, nextH, nextV);
            indices[idx++] = int3(nextV, nextH, nextHV);
        }
    }
}

void Mesh::calculateNormals() {
    for (auto& v : vertices) {
        v.normal = float3(0.0f, 0.0f, 0.0f);
    }

    for (const auto& tri : indices) {
        const float3& a = vertices[tri.a].position;
        const float3& b = vertices[tri.b].position;
        const float3& c = vertices[tri.c].position;

        float3 ab = b - a;
        float3 ac = c - a;

        float3 n = normalize(cross(ac, ab));

        vertices[tri.a].normal += n;
        vertices[tri.b].normal += n;
        vertices[tri.c].normal += n;
    }

    for (auto& v : vertices) {
        v.normal = normalize(v.normal);
    }
}

void Mesh::applyMapping(MappingType type) {
    if (vertices.empty())
        return;

    float3 minP = vertices[0].position;
    float3 maxP = vertices[0].position;

    for (const auto& v : vertices) {
        minP.x = std::min(minP.x, v.position.x);
        minP.y = std::min(minP.y, v.position.y);
        minP.z = std::min(minP.z, v.position.z);

        maxP.x = std::max(maxP.x, v.position.x);
        maxP.y = std::max(maxP.y, v.position.y);
        maxP.z = std::max(maxP.z, v.position.z);
    }

    float3 center = (minP + maxP) * 0.5f;
    float3 size = maxP - minP;

    if (size.x < 0.0001f)
        size.x = 1.0f;
    if (size.y < 0.0001f)
        size.y = 1.0f;
    if (size.z < 0.0001f)
        size.z = 1.0f;

    for (auto& v : vertices) {
        float x = v.position.x - center.x;
        float y = v.position.y - center.y;
        float z = v.position.z - center.z;

        switch (type) {
        case MappingType::PLANAR: {
            v.u = (x / size.x) + 0.5f;
            v.v = (z / size.z) + 0.5f;
            break;
        }

        case MappingType::SPHERICAL: {
            float r = std::sqrt(x * x + y * y + z * z);
            if (r < 0.0001f) {
                v.u = 0.5f;
                v.v = 0.5f;
                break;
            }

            float angleU = std::atan2(z, x);
            v.u = (angleU / (2.0f * M_PI)) + 0.5f;
            float angleV = std::asin(y / r);
            v.v = (angleV / M_PI) + 0.5f;
            break;
        }

        case MappingType::CYLINDRICAL: {
            float angleU = std::atan2(z, x);
            v.u = (angleU / (2.0f * M_PI)) + 0.5f;

            v.v = (y / size.y) + 0.5f;
            break;
        }

        case MappingType::CUBIC: {
            float3 n = v.normal;
            float absNX = std::abs(n.x);
            float absNY = std::abs(n.y);
            float absNZ = std::abs(n.z);

            if (absNZ >= absNX && absNZ >= absNY) {
                if (n.z > 0) {
                    v.u = (x / size.x) + 0.5f;
                    v.v = (y / size.y) + 0.5f;
                } else {
                    v.u = (-x / size.x) + 0.5f;
                    v.v = (y / size.y) + 0.5f;
                }
            } else if (absNX >= absNY) {
                if (n.x > 0) {
                    v.u = (-z / size.z) + 0.5f;
                    v.v = (y / size.y) + 0.5f;
                } else {
                    v.u = (z / size.z) + 0.5f;
                    v.v = (y / size.y) + 0.5f;
                }
            } else {
                if (n.y > 0) {
                    v.u = (x / size.x) + 0.5f;
                    v.v = (-z / size.z) + 0.5f;
                } else {
                    v.u = (x / size.x) + 0.5f;
                    v.v = (z / size.z) + 0.5f;
                }
            }
            break;
        }
        }

        v.u = std::max(0.0f, std::min(1.0f, v.u));
        v.v = std::max(0.0f, std::min(1.0f, v.v));
    }
}
