#pragma once

#include "core/color.h"
#include "core/image.h"
#include "math/geometry.h"

class Renderer {
  private:
    /**
     * @brief Checks whether the point is within the triangle using half space function.
     *
     * @param triangle The triangle to test against. Winding order should be counterclockwise.
     * @param point The point to check.
     * @return true if point is inside the triangle, false otherwise.
     */
    static bool isInsideTriangle(const Triangle& triangle, const Point& point);

    /**
     * @brief Converts canonical coordinates [-1, 1] to image space [0, width], [0, height].
     *
     * @param point Canonical coordinates of point to be converted.
     * @param image Full image containing information about width and height.
     * @return Point in image space.
     */
    static Point toImageSpace(const Point& point, const Image& image);

  public:
    /**
     * @brief Draws triangle from top left corner to bottom right.
     *
     * @param image Image where the triangle will be drawn.
     * @param triangle Triangle to be drawn.
     * @param color Color of the triangle.
     */
    static void drawTriangle(Image& image, const Triangle& triangle, const Color& color);
};
