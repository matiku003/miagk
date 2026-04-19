#pragma once

#include "core/color.h"
#include "core/image.h"
#include "math/geometry.h"

class Rasterizer {
  private:
    /**
     * @brief Checks whether the point is within the triangle using half space function.
     *
     * @param triangle The triangle to test against. Winding order should be clockwise.
     * @param point The point to check.
     * @return true if point is inside the triangle, false otherwise.
     */
    static bool isInsideTriangle(const Triangle& triangle, const Point& point);

    /**
     * @brief Checks whether the triangle's front is facing the camera.
     *
     * @param triangle The triangle to test against. Winding order should be clockwise.
     * @return true if the triangle's winding order is clockwise, false otherwise.
     */
    static bool isFrontFacing(const Triangle& triangle);

    /**
     * @brief Converts canonical coordinates [-1, 1] to image space [0, width], [0, height].
     *
     * @param point Canonical coordinates of point to be converted.
     * @param image Full image containing information about width and height. Image has top-left origin.
     * @return Point in image space.
     */
    static Point toImageSpace(const Point& point, const Image& image);

    /**
     * @brief Clamps axis-aligned bounding box to image boundaries.
     *
     * @param bounds Input bounding box in image space.
     * @param img Image used as boundary reference.
     * @return Clamped AABB constrained to image dimensions.
     */
    static AABB clampAABBToImage(const AABB& bounds, const Image& img);

  public:
    /**
     * @brief Draws triangle from bottom left corner to top right.
     *
     * @param image Image where the triangle will be drawn.
     * @param triangle Triangle to be drawn.
     * @param color Color of the triangle.
     */
    static void drawTriangle(Image& image, const Triangle& triangle, const Color& color);
};
