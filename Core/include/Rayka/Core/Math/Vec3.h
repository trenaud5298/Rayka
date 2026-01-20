#ifndef RAYKA_CORE_VEC3_H
#define RAYKA_CORE_VEC3_H

namespace Rayka {
    struct Vec3 {
        float x,y,z;

        // Constructors
        constexpr Vec3() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
        constexpr Vec3(float v) noexcept : x(v), y(v), z(v) {}
        constexpr Vec3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}

        // Operators (Self)
        constexpr Vec3 operator-() const noexcept { return {-x, -y, -z}; }
        constexpr Vec3& operator+=(Vec3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
        constexpr Vec3& operator-=(Vec3 v) noexcept { x -= v.x; y += v.y; z += v.z; return *this; }
        constexpr Vec3& operator*=(float s) noexcept { x *= s; y *= s; z *= s; return *this; }

    };

    // Free Operators
    constexpr Vec3 operator+(Vec3 a, Vec3 b) noexcept { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
    constexpr Vec3 operator-(Vec3 a, Vec3 b) noexcept { return {a.x -b.x, a.y - b.y, a.z - b.z}; }
    constexpr Vec3 operator*(Vec3 v, float s) noexcept { return {v.x * s, v.y * s, v.z * s}; }
    constexpr Vec3 operator*(float s, Vec3 v) noexcept { return {v.x * s, v.y * s, v.z * s}; }

    // Math Functions
    constexpr float dot(Vec3 a, Vec3 b) noexcept { return a.x*b.x + a.y*b.y + a.z*b.z; }
    constexpr Vec3 cross(Vec3 a, Vec3 b) noexcept { return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; }
}

#endif