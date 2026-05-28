#pragma once

#include <cstdlib>
#include <vector>

#include "buffer/framebuffer.h"
#include "light/light.h"
#include "math/barycentric.h"
#include "math/geometry.h"

/**
 * @brief Represents a triangle with precomputed edge data for optimized rasterization.
 *
 * This structure stores vertices along with pre-calculated differences (dx, dy)
 * and the inverse denominator. Precomputing these values outside the pixel loops
 * significantly reduces the number of subtractions and divisions.
 */
struct PreparedTriangle {
    Point a, b, c;
    float dx12, dy12, dx23, dy23, dx31, dy31;
    float inverseDenominator;

    /**
     * @brief Constructs a PreparedTriangle and precomputes all necessary edge data.
     *
     * @param triangle The source triangle, typically already transformed to image space.
     */
    PreparedTriangle(const Triangle& triangle) : a(triangle.a), b(triangle.b), c(triangle.c) {
        dx12 = a.position.x - b.position.x;
        dy12 = a.position.y - b.position.y;
        dx23 = b.position.x - c.position.x;
        dy23 = b.position.y - c.position.y;
        dx31 = c.position.x - a.position.x;
        dy31 = c.position.y - a.position.y;

        float denominator = (dy23 * (-dx31)) + ((-dx23) * (-dy31));
        inverseDenominator = (std::abs(denominator) > 1e-7f) ? (1.0f / denominator) : 0.0f;
    }
};

class Rasterizer {
  private:
    /**
     * @brief Checks whether the point is within the triangle using half space function.
     *
     * Function uses top-left filling convention.
     *
     * @param triangle The triangle to test against. Winding order should be clockwise.
     * @param point The point to check.
     * @return true if point is inside the triangle, false otherwise.
     */
    [[nodiscard]] static bool isInsideTriangle(const PreparedTriangle& triangle, const Point& point);

    /**
     * @brief Checks whether the triangle's front is facing the camera (right-handed coordinate system).
     *
     * @param triangle The triangle to test against. Winding order should be clockwise.
     * @return true if the triangle's winding order is clockwise, false otherwise.
     */
    [[nodiscard]] static bool isFrontFacing(const PreparedTriangle& triangle);

    /**
     * @brief Converts canonical coordinates [-1, 1] to image space [0, width], [0, height].
     *
     * @param point Canonical coordinates of point to be converted.
     * @param buffer Framebuffer used to derive resolution.
     * @return Point in image space.
     */
    [[nodiscard]] static Point toImageSpace(const Point& point, const Framebuffer& buffer);

    /**
     * @brief Computes barycentric coordinates of a point with respect to a triangle.
     *
     * @param triangle Input triangle in 2D space.
     * @param point Point to transform into barycentric coordinates.
     * @return Barycentric weights for triangle vertices.
     */
    [[nodiscard]] static Barycentric getBarycentricCoordinates(const PreparedTriangle& triangle, const Point& point);

    /**
     * @brief Clamps axis-aligned bounding box to image boundaries.
     *
     * @param bounds Input bounding box in image space.
     * @param buffer Framebuffer used for size limits.
     * @return Clamped AABB constrained to image dimensions.
     */
    [[nodiscard]] static AABB clampAABBToImage(const AABB& bounds, const Framebuffer& buffer);

  public:
    /**
     * @brief Draws triangle from top-left corner to bottom-right.
     *
     * @param buffer Target framebuffer.
     * @param triangle Triangle to be drawn.
     * @param lights List of lights used in the scene for phong shading.
     * @param transform Transform used for light calcualtions.
     * @param phong Determines whether Phong or Gouraud shading is used.
     */
    static void drawTriangle(Framebuffer& buffer,
                             const Triangle& triangle,
                             const std::vector<Light*>& lights,
                             const TransformSystem& transform,
                             bool phong);
};
