#pragma once

#include "core/color.h"
#include "core/image.h"
#include "math/geometry.h"
#include "math/math.h"

class Rasterizer {
  private:
    /**
     * @brief Checks whether the point is within the triangle using half space function.
     *
     * @param triangle The triangle to test against. Winding order should be clockwise.
     * @param point The point to check.
     * @return true if point is inside the triangle, false otherwise.
     */
    [[nodiscard]] static bool isInsideTriangle(const Triangle& triangle, const Point& point);

    /**
     * @brief Checks whether the triangle's front is facing the camera (right-handed coordinate system).
     *
     * @param triangle The triangle to test against. Winding order should be clockwise.
     * @return true if the triangle's winding order is clockwise, false otherwise.
     */
    [[nodiscard]] static bool isFrontFacing(const Triangle& triangle);

    /**
     * @brief Converts canonical coordinates [-1, 1] to image space [0, width], [0, height].
     *
     * @param point Canonical coordinates of point to be converted.
     * @param image Full image containing information about width and height. Image has bottom-left origin.
     * @return Point in image space.
     */
    [[nodiscard]] static Point toImageSpace(const Point& point, const Image& image);

    /**
     * @brief Computes interpolated color at a point inside a triangle.
     *
     * @param triangle The input triangle.
     * @param barycentricCoords Barycentric coordinates of the point.
     * @return Interpolated color at the given point.
     */
    [[nodiscard]] static Color getInterpolatedColor(const Triangle& triangle, const Barycentric& barycentricCoords);

    /**
     * @brief Clamps axis-aligned bounding box to image boundaries.
     *
     * @param bounds Input bounding box in image space.
     * @param img Image used as boundary reference.
     * @return Clamped AABB constrained to image dimensions.
     */
    [[nodiscard]] static AABB clampAABBToImage(const AABB& bounds, const Image& img);

  public:
    /**
     * @brief Draws triangle from top-left corner to bottom-right.
     *
     * @param image Image where the triangle will be drawn.
     * @param triangle Triangle to be drawn.
     */
    static void drawTriangle(Image& image, const Triangle& triangle);
};
