#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

#include "buffer/framebuffer.h"
#include "light/directionalLight.h"
#include "light/light.h"
#include "light/pointLight.h"
#include "light/spotlight.h"
#include "math/geometry.h"
#include "math/pipeline.h"
#include "math/transform.h"
#include "math/vector.h"
#include "mesh/mesh.h"
#include "rasterizer/fragment.h"
#include "rasterizer/rasterizer.h"
#include "utils/imageExporter.h"
#include "utils/imageImporter.h"

static void drawMeshGouraud(Framebuffer& framebuffer,
                            const TransformSystem& transform,
                            const Mesh& mesh,
                            const std::vector<Light*>& lights,
                            const ColorBuffer& texture) {

    for (const auto& tri : mesh.indices) {
        const auto& vA = mesh.vertices[tri.a];
        const auto& vB = mesh.vertices[tri.b];
        const auto& vC = mesh.vertices[tri.c];

        float3 lightA(0, 0, 0);
        float3 lightB(0, 0, 0);
        float3 lightC(0, 0, 0);

        auto transformToWorld = [&](const Point& v) {
            float4 posW = transform.obj2world * float4{v.position.x, v.position.y, v.position.z, 1.0f};
            float4 normW = transform.obj2world * float4{v.normal.x, v.normal.y, v.normal.z, 0.0f};
            return std::make_pair(float3{posW.x, posW.y, posW.z}, normalize(float3{normW.x, normW.y, normW.z}));
        };

        auto [worldPosA, worldNormalA] = transformToWorld(vA);
        auto [worldPosB, worldNormalB] = transformToWorld(vB);
        auto [worldPosC, worldNormalC] = transformToWorld(vC);

        for (auto* light : lights) {
            lightA += light->calculate(transform, Fragment{worldPosA, worldNormalA});
            lightB += light->calculate(transform, Fragment{worldPosB, worldNormalB});
            lightC += light->calculate(transform, Fragment{worldPosC, worldNormalC});
        }

        float3 finalColorA = lightA;
        float3 finalColorB = lightB;
        float3 finalColorC = lightC;

        // float3 finalColorA = float3(1.0f, 0.0f, 0.0f) * lightA;
        // float3 finalColorB = float3(0.0f, 1.0f, 0.0f) * lightB;
        // float3 finalColorC = float3(0.0f, 0.0f, 1.0f) * lightC;

        Rasterizer::drawTriangle(
            framebuffer,
            Triangle{applyMVP(transform, {vA.position, finalColorA, vA.normal, vA.worldPosition, vA.u, vA.v}),
                     applyMVP(transform, {vB.position, finalColorB, vB.normal, vB.worldPosition, vB.u, vB.v}),
                     applyMVP(transform, {vC.position, finalColorC, vC.normal, vC.worldPosition, vC.u, vC.v})},
            lights,
            transform,
            texture,
            false);
    }
}

static void drawMeshPhong(Framebuffer& framebuffer,
                          const TransformSystem& transform,
                          const Mesh& mesh,
                          const std::vector<Light*>& lights,
                          const ColorBuffer& texture) {

    for (const auto& tri : mesh.indices) {
        const auto& vA = mesh.vertices[tri.a];
        const auto& vB = mesh.vertices[tri.b];
        const auto& vC = mesh.vertices[tri.c];

        // float3 finalColorA = float3(1.0f, 0.0f, 0.0f) * lightA;
        // float3 finalColorB = float3(0.0f, 1.0f, 0.0f) * lightB;
        // float3 finalColorC = float3(0.0f, 0.0f, 1.0f) * lightC;

        Rasterizer::drawTriangle(
            framebuffer,
            Triangle{applyMVP(transform, {vA.position, {}, vA.normal, vA.worldPosition, vA.u, vA.v}),
                     applyMVP(transform, {vB.position, {}, vB.normal, vB.worldPosition, vB.u, vB.v}),
                     applyMVP(transform, {vC.position, {}, vC.normal, vC.worldPosition, vC.u, vC.v})},
            lights,
            transform,
            texture,
            true);
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    TransformSystem transform1, transform2, transform3;
    transform1.setPerspective(60.0f, 1.0f, 0.1f, 100.0f);
    transform1.setLookAt({0, 3, 3}, {0, 0, 0}, {0, 1, 0});
    transform2.setPerspective(60.0f, 1.0f, 0.1f, 100.0f);
    transform2.setLookAt({0, 3, 3}, {0, 0, 0}, {0, 1, 0});
    transform3.setPerspective(60.0f, 1.0f, 0.1f, 100.0f);
    transform3.setLookAt({0, 3, 3}, {0, 0, 0}, {0, 1, 0});

    Framebuffer framebuffer1(1024, 1024);
    Framebuffer framebuffer2(1024, 1024);

    float3 gray = {0.3f, 0.3f, 0.3f};

    framebuffer1.clear(gray);
    framebuffer2.clear(gray);

    Mesh cube, sphere, cylinder;

    DirectionalLight directional;
    directional.position = {-1.0f, -1.0f, -1.0f};
    directional.ambient = {0.1f, 0.1f, 0.1f};
    directional.diffuse = {1.0f, 1.0f, 1.0f};
    directional.specular = {1.0f, 1.0f, 1.0f};
    directional.shininess = 100.0f;

    std::vector<Light*> lights = {&directional};
    std::vector<Light*> emptyLights = {};

    ColorBuffer stoneTexture = ImageImporter::loadTGA("textures/stone.tga");
    ColorBuffer waterTexture = ImageImporter::loadTGA("textures/water.tga");

    int steps = 20;

    cube.buildCube();
    transform1.multiplyByTranslation(float3(0, 1, 0));
    cube.calculateNormals();
    cube.applyMapping(MappingType::CUBIC);
    drawMeshPhong(framebuffer1, transform1, cube, emptyLights, stoneTexture);

    sphere.buildSphere(steps, steps);
    transform2.multiplyByTranslation(float3(-1, 0, 0));
    sphere.calculateNormals();
    sphere.applyMapping(MappingType::SPHERICAL);
    drawMeshPhong(framebuffer1, transform2, sphere, lights, stoneTexture);

    cylinder.buildCylinder(steps, steps);
    transform3.multiplyByTranslation(float3(1, 0, 0));
    cylinder.calculateNormals();
    cylinder.applyMapping(MappingType::CYLINDRICAL);
    drawMeshPhong(framebuffer1, transform3, cylinder, lights, waterTexture);

    ImageExporter::saveTGA(framebuffer1.getColorBuffer(), "outputPhong.tga");

    drawMeshGouraud(framebuffer2, transform1, cube, emptyLights, stoneTexture);
    drawMeshGouraud(framebuffer2, transform2, sphere, lights, stoneTexture);
    drawMeshGouraud(framebuffer2, transform3, cylinder, lights, waterTexture);

    ImageExporter::saveTGA(framebuffer2.getColorBuffer(), "outputGouraud.tga");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms\n";

    return 0;
}
