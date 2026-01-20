// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, Tyler Renaud

#ifndef RAYKA_CORE_MESH_H
#define RAYKA_CORE_MESH_H

// Rayka Includes
#include <Rayka/Core/Export.h>

// C++ Includes
#include <vector>
#include <cstdint>

namespace Rayka {
    struct RAYKA_CORE_EXPORT Vertex {
        float position[3];
        float uv[2];
    };

    struct RAYKA_CORE_EXPORT Mesh {
        std::vector<Vertex> vertices;
        std::vector<std::uint32_t> indices;
    };
}

#endif