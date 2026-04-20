#pragma once

/**
 * @brief Represents an RGB color (float per channel) in [0-1] range.
 */
struct Color {
    float r = 0;
    float g = 0;
    float b = 0;

    [[nodiscard]] constexpr Color operator*(float f) const {
        return {r * f, g * f, b * f};
    }

    [[nodiscard]] constexpr Color operator+(const Color& other) const {
        return {r + other.r, g + other.g, b + other.b};
    }
};

[[nodiscard]] constexpr Color operator*(float f, const Color& c) {
    return c * f;
}
