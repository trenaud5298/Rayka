#ifndef RAYKA_CORE_VEC2_H
#define RAYKA_CORE_VEC2_H

// Rayka Includes
#include <Rayka/Core/Export.h>

// C++ Includes
#include <cmath>

namespace Rayka {
    struct RAYKA_CORE_EXPORT Vec2 {
        float x, y;

        // Constructors
        constexpr Vec2() noexcept : x(0.0f), y(0.0f) {}
        constexpr Vec2(float v) noexcept : x(v), y(v) {}
        constexpr Vec2(float x, float y) noexcept : x(x), y(y) {}

        // Operators (Self)
        constexpr Vec2 operator-() const noexcept { return {-x, -y}; }
        constexpr Vec2& operator+=(Vec2 v) noexcept { x += v.x; y += v.y; return *this; }
        constexpr Vec2& operator-=(Vec2 v) noexcept { x -= v.x; y -= v.y; return *this; }
        constexpr Vec2& operator*=(float s) noexcept { x *= s; y *= s; return *this; }
        constexpr Vec2& operator/=(float s) noexcept { return *this *= (1.0f / s); } // Undefined behavior for s == 0 (matches IEEE-754 behavior)

        // Math Functions
        [[nodiscard]] constexpr float norm2() const noexcept { return x*x + y*y; }
        [[nodiscard]] float norm() const noexcept { return std::sqrt(norm2()); }
        [[nodiscard]] float invNorm() const noexcept { return 1.0f / norm(); }
        [[nodiscard]] Vec2 normalized() const noexcept { float inv = invNorm(); return {x*inv, y*inv}; }
        Vec2& normalize() noexcept { return *this *= invNorm(); }
    };

    // Free Operators
    [[nodiscard]] constexpr Vec2 operator+(Vec2 a, Vec2 b) noexcept { return {a.x + b.x, a.y + b.y}; }
    [[nodiscard]] constexpr Vec2 operator-(Vec2 a, Vec2 b) noexcept { return {a.x -b.x, a.y - b.y}; }
    [[nodiscard]] constexpr Vec2 operator*(Vec2 v, float s) noexcept { return {v.x * s, v.y * s}; }
    [[nodiscard]] constexpr Vec2 operator*(float s, Vec2 v) noexcept { return {v.x * s, v.y * s}; }
    [[nodiscard]] constexpr Vec2 operator*(Vec2 a, Vec2 b) noexcept { return {a.x*b.x, a.y*b.y}; }
    [[nodiscard]] constexpr Vec2 operator/(Vec2 v, float s) noexcept { return Vec2(v)/=s; }

    // Free Math Functions
    [[nodiscard]] constexpr float dot(Vec2 a, Vec2 b) noexcept { return a.x*b.x + a.y*b.y; }
    [[nodiscard]] inline bool nearlyEqual(Vec2 a, Vec2 b, float eps = 1e-6f) noexcept { return std::fabs(a.x-b.x) < eps && std::fabs(a.y-b.y) < eps; }
}

#endif