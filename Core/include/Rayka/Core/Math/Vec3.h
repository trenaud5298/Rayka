#ifndef RAYKA_CORE_VEC3_H
#define RAYKA_CORE_VEC3_H

// Rayka Includes
#include <Rayka/Core/Export.h>

// C++ Includes
#include <cmath>

namespace Rayka {
    struct RAYKA_CORE_EXPORT Vec3 {
        float x, y, z;

        // Constructors
        constexpr Vec3() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
        constexpr Vec3(float v) noexcept : x(v), y(v), z(v) {}
        constexpr Vec3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}

        // Operators (Self)
        constexpr Vec3 operator-() const noexcept { return {-x, -y, -z}; }
        constexpr Vec3& operator+=(Vec3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
        constexpr Vec3& operator-=(Vec3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
        constexpr Vec3& operator*=(float s) noexcept { x *= s; y *= s; z *= s; return *this; }
        constexpr Vec3& operator/=(float s) noexcept { return *this *= (1.0f / s); } // Undefined behavior for s == 0 (matches IEEE-754 behavior)

        // Math Functions
        [[nodiscard]] constexpr float norm2() const noexcept { return x*x + y*y + z*z; }
        [[nodiscard]] float norm() const noexcept { return std::sqrt(norm2()); }
        [[nodiscard]] float invNorm() const noexcept { return 1.0f / norm(); }
        [[nodiscard]] Vec3 normalized() const noexcept { float inv = invNorm(); return {x*inv, y*inv, z*inv}; }
        Vec3& normalize() noexcept { return *this *= invNorm(); }
    };

    // Free Operators
    [[nodiscard]] constexpr Vec3 operator+(Vec3 a, Vec3 b) noexcept { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
    [[nodiscard]] constexpr Vec3 operator-(Vec3 a,  Vec3 b) noexcept { return {a.x -b.x, a.y - b.y, a.z - b.z}; }
    [[nodiscard]] constexpr Vec3 operator*(Vec3 v, float s) noexcept { return {v.x * s, v.y * s, v.z * s}; }
    [[nodiscard]] constexpr Vec3 operator*(float s, Vec3 v) noexcept { return {v.x * s, v.y * s, v.z * s}; }
    [[nodiscard]] constexpr Vec3 operator*(Vec3 a, Vec3 b) noexcept { return {a.x*b.x, a.y*b.y, a.z*b.z}; }
    [[nodiscard]] constexpr Vec3 operator/(Vec3 v, float s) noexcept { return Vec3(v)/=s; }

    // Free Math Functions
    [[nodiscard]] constexpr float dot(Vec3 a, Vec3 b) noexcept { return a.x*b.x + a.y*b.y + a.z*b.z; }
    [[nodiscard]] constexpr Vec3 cross(Vec3 a, Vec3 b) noexcept { return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; }
    [[nodiscard]] inline bool nearlyEqual(Vec3 a, Vec3 b, float eps = 1e-6f) noexcept { return std::fabs(a.x-b.x) < eps && std::fabs(a.y-b.y) < eps && std::fabs(a.z-b.z) < eps; }
}

#endif