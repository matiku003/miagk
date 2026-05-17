#pragma once

#include <vector>

#include "math/geometry.h"
#include "math/vector.h"

class Mesh {
  public:
    std::vector<Point> vertices;
    std::vector<int3> indices;

    /**
     * @brief Builds a single triangle mesh.
     */
    void buildTriangle();

    /**
     * @brief Builds a cube mesh.
     */
    void buildCube();

    /**
     * @brief Builds a pyramid mesh.
     */
    void buildPyramid();

    /**
     * @brief Builds a tetrahedron mesh.
     */
    void buildTetrahedron();

    /**
     * @brief Builds a cone mesh.
     * @param step Number of segments around the base circle.
     */
    void buildCone(int step);

    /**
     * @brief Builds a cylinder mesh.
     * @param verticalStep Number of segments around the radius (sides).
     * @param horizontalStep Number of segments along height.
     */
    void buildCylinder(int verticalStep, int horizontalStep);

    /**
     * @brief Builds a sphere mesh.
     * @param verticalStep Number of segments around the equator.
     * @param horizontalStep Number of segments from top to bottom.
     */
    void buildSphere(int verticalStep, int horizontalStep);

    /**
     * @brief Builds a torus mesh.
     * @param verticalStep Segments around the tube.
     * @param horizontalStep Segments around the ring.
     */
    void buildTorus(int verticalStep, int horizontalStep);

    /**
     * @brief Computes vertex normals.
     */
    void calculateNormals();
};
