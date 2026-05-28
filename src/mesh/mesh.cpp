#include "mesh/mesh.h"

#include <cmath>
#include <vector>

#include "math/geometry.h"
#include "math/math.h"
#include "math/vector.h"

void Mesh::buildTriangle() {
    vertices.resize(3);
    indices.resize(1);
    vertices[0].position = float3(-0.5f, 0.0f, 0.0f);
    vertices[1].position = float3(0.0f, 0.5f, 0.0f);
    vertices[2].position = float3(0.5f, 0.0f, 0.0f);
    indices[0] = int3(0, 1, 2);
}

void Mesh::buildCube() {
    vertices.resize(8);
    indices.resize(12);

    vertices[0].position = float3(-0.5f, -0.5f, 0.5f);
    vertices[1].position = float3(-0.5f, 0.5f, 0.5f);
    vertices[2].position = float3(0.5f, -0.5f, 0.5f);
    vertices[3].position = float3(0.5f, 0.5f, 0.5f);

    vertices[4].position = float3(-0.5f, -0.5f, -0.5f);
    vertices[5].position = float3(-0.5f, 0.5f, -0.5f);
    vertices[6].position = float3(0.5f, -0.5f, -0.5f);
    vertices[7].position = float3(0.5f, 0.5f, -0.5f);

    // front
    indices[0] = int3(0, 1, 2);
    indices[1] = int3(2, 1, 3);

    // back
    indices[2] = int3(4, 6, 5);
    indices[3] = int3(6, 7, 5);

    // left
    indices[4] = int3(4, 5, 0);
    indices[5] = int3(0, 5, 1);

    // right
    indices[6] = int3(2, 3, 6);
    indices[7] = int3(6, 3, 7);

    // top
    indices[8] = int3(1, 5, 3);
    indices[9] = int3(3, 5, 7);

    // bottom
    indices[10] = int3(4, 0, 6);
    indices[11] = int3(6, 0, 2);
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
