#pragma once

#include <vector>

class DepthBuffer {
  private:
    unsigned int width = 0;
    unsigned int height = 0;
    std::vector<float> depthBuffer;

  public:
    /**
     * @brief Creates a depth buffer with given resolution.
     *
     * @param width Width in pixels.
     * @param height Height in pixels.
     */
    DepthBuffer(unsigned int width, unsigned int height);

    /**
     * @brief Resizes the depth buffer to a new resolution.
     *
     * @param newWidth New width in pixels.
     * @param newHeight New height in pixels.
     */
    void resize(unsigned int newWidth, unsigned int newHeight);

    /**
     * @brief Clears the depth buffer with a constant value.
     *
     * @param depth Value used to reset all depth entries.
     */
    void clear(float depth);

    /**
     * @brief Tests whether a new depth value is closer than the stored one.
     *
     * @param index Pixel index (y * width + x).
     * @param depth Depth value to compare.
     * @return true if the new depth passes the test.
     */
    bool isCloser(size_t index, float depth) const;

    /**
     * @brief Writes a depth value to the buffer.
     *
     * @param index Pixel index (y * width + x).
     * @param depth Depth value to store.
     */
    void setDepth(size_t index, float depth);

    /**
     * @brief Returns buffer width in pixels.
     */
    unsigned int getWidth() const;

    /**
     * @brief Returns buffer height in pixels.
     */
    unsigned int getHeight() const;
};
