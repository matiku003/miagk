#include <chrono>
#include <iostream>

#include "buffer/framebuffer.h"
#include "math/geometry.h"
#include "math/pipeline.h"
#include "math/transform.h"
#include "math/vector.h"
#include "mesh/mesh.h"
#include "rasterizer/rasterizer.h"
#include "utils/imageExporter.h"

static void drawMesh(Framebuffer& framebuffer, const TransformSystem& transform, const Mesh& mesh) {
    for (const auto& tri : mesh.indices) {
        Rasterizer::drawTriangle(
            framebuffer,
            Triangle{applyMVP(transform, {mesh.vertices[tri.a].position, float3(1.0f, 0.0f, 0.0f)}),
                     applyMVP(transform, {mesh.vertices[tri.b].position, float3(0.0f, 1.0f, 0.0f)}),
                     applyMVP(transform, {mesh.vertices[tri.c].position, float3(0.0f, 0.0f, 1.0f)})});
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    TransformSystem transform;

    transform.setPerspective(60.0f, 1.0f, 0.1f, 100.0f);

    transform.setLookAt({4, 4, 4}, {0, 0, 0}, {0, 1, 0});

    Framebuffer framebuffer(1024, 1024);

    float3 gray = {0.3f, 0.3f, 0.3f};

    framebuffer.clear(gray);

    Mesh triangle, cube, pyramid, tetrahedron, cone, cylinder, sphere, torus;

    // triangle.buildTriangle();
    // triangle.calculateNormals();
    // triangle.setColor();
    // drawMesh(framebuffer, transform, triangle);

    cube.buildCube();
    cube.calculateNormals();
    transform.multiplyByTranslation(float3(-2, 0, -2));
    drawMesh(framebuffer, transform, cube);

    pyramid.buildPyramid();
    pyramid.calculateNormals();
    transform.multiplyByTranslation(float3(2, 0, 0));
    drawMesh(framebuffer, transform, pyramid);

    tetrahedron.buildTetrahedron();
    tetrahedron.calculateNormals();
    transform.multiplyByTranslation(float3(2, 0, 0));
    drawMesh(framebuffer, transform, tetrahedron);

    int steps = 20;

    cone.buildCone(steps);
    cone.calculateNormals();
    transform.multiplyByTranslation(float3(0, 0, 2));
    drawMesh(framebuffer, transform, cone);

    cylinder.buildCylinder(steps, steps);
    cylinder.calculateNormals();
    transform.multiplyByTranslation(float3(-2, 0, 0));
    drawMesh(framebuffer, transform, cylinder);

    sphere.buildSphere(steps, steps);
    sphere.calculateNormals();
    transform.multiplyByTranslation(float3(-2, 0, 0));
    drawMesh(framebuffer, transform, sphere);

    torus.buildTorus(steps, steps);
    torus.calculateNormals();
    transform.multiplyByTranslation(float3(2, 0, 2));
    drawMesh(framebuffer, transform, torus);

    ImageExporter::saveTGA(framebuffer.getColorBuffer(), "output.tga");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms\n";

    return 0;
}
