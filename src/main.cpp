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

static void drawMesh(Framebuffer& framebuffer,
                     const TransformSystem& transform,
                     const Mesh& mesh,
                     const std::vector<Light*>& lights) {

    for (const auto& tri : mesh.indices) {
        const auto& vA = mesh.vertices[tri.a];
        const auto& vB = mesh.vertices[tri.b];
        const auto& vC = mesh.vertices[tri.c];

        float3 lightA(0, 0, 0);
        float3 lightB(0, 0, 0);
        float3 lightC(0, 0, 0);

        for (auto* light : lights) {
            lightA += light->calculate(transform, Fragment{vA.position, vA.normal});
            lightB += light->calculate(transform, Fragment{vB.position, vB.normal});
            lightC += light->calculate(transform, Fragment{vC.position, vC.normal});
        }

        float3 finalColorA = lightA;
        float3 finalColorB = lightB;
        float3 finalColorC = lightC;

        // float3 finalColorA = float3(1.0f, 0.0f, 0.0f) * lightA;
        // float3 finalColorB = float3(0.0f, 1.0f, 0.0f) * lightB;
        // float3 finalColorC = float3(0.0f, 0.0f, 1.0f) * lightC;

        Rasterizer::drawTriangle(framebuffer,
                                 Triangle{applyMVP(transform, {vA.position, finalColorA}),
                                          applyMVP(transform, {vB.position, finalColorB}),
                                          applyMVP(transform, {vC.position, finalColorC})});
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    TransformSystem transform1, transform2, transform3;
    transform1.setPerspective(60.0f, 1.0f, 0.1f, 100.0f);
    transform1.setLookAt({0, 0, 3}, {0, 0, 0}, {0, 1, 0});
    transform2.setPerspective(60.0f, 1.0f, 0.1f, 100.0f);
    transform2.setLookAt({0, 0, 3}, {0, 0, 0}, {0, 1, 0});
    transform3.setPerspective(60.0f, 1.0f, 0.1f, 100.0f);
    transform3.setLookAt({0, 0, 3}, {0, 0, 0}, {0, 1, 0});

    Framebuffer framebuffer(1024, 1024);

    float3 gray = {0.3f, 0.3f, 0.3f};

    framebuffer.clear(gray);

    Mesh cone, sphere, torus;

    DirectionalLight directional;
    directional.position = {0.0f, -1.0f, 0.0f};
    directional.ambient = {0.1f, 0.1f, 0.1f};
    directional.diffuse = {1.0f, 0.0f, 0.0f};
    directional.specular = {1.0f, 1.0f, 1.0f};
    directional.shininess = 100.0f;

    PointLight point;
    point.position = {0.0f, 0.0f, 0.0f};
    point.ambient = {0.1f, 0.1f, 0.1f};
    point.diffuse = {0.0f, 1.0f, 0.0f};
    point.specular = {1.0f, 1.0f, 1.0f};
    point.shininess = 5.0f;

    Spotlight spot;
    spot.position = {1.0f, 0.0f, 1.5f};
    spot.direction = {0.0f, 0.0f, -1.0f};
    spot.ambient = {0.05f, 0.05f, 0.05f};
    spot.diffuse = {0.0f, 0.0f, 1.0f};
    spot.specular = {1.0f, 1.0f, 1.0f};
    spot.shininess = 32.0f;
    spot.cutoff = std::cos(15.0f * 3.14159f / 180.0f);
    spot.outerCutoff = std::cos(20.0f * 3.14159f / 180.0f);
    spot.constant = 1.0f;
    spot.linear = 0.09f;

    std::vector<Light*> lights = {&directional, &point, &spot};

    int steps = 20;

    cone.buildCone(steps);
    transform1.multiplyByTranslation(float3(0, 1, 0));
    cone.calculateNormals();
    drawMesh(framebuffer, transform1, cone, lights);

    sphere.buildTorus(steps, steps);
    transform2.multiplyByRotation(90, float3(1, 0, 0));
    transform2.multiplyByTranslation(float3(-1, 0, 0));
    sphere.calculateNormals();
    drawMesh(framebuffer, transform2, sphere, lights);

    torus.buildSphere(steps, steps);
    transform3.multiplyByTranslation(float3(1, 0, 0));
    torus.calculateNormals();
    drawMesh(framebuffer, transform3, torus, lights);

    ImageExporter::saveTGA(framebuffer.getColorBuffer(), "output.tga");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms\n";

    return 0;
}
