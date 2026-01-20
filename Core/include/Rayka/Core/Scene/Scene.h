// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, Tyler Renaud

#ifndef RAYKA_CORE_SCENE_H
#define RAYKA_CORE_SCENE_H

// Rayka Includes
#include <Rayka/Core/Export.h>
#include <Rayka/Core/Scene/Mesh.h>
#include <Rayka/Core/Scene/Instance.h>

// C++ Includes
#include <vector>
#include <cstddef>

namespace Rayka {
    class RAYKA_CORE_EXPORT Scene {
    public:
        Scene();

        std::size_t addMesh(const Mesh& mesh);
        const Mesh& getMesh(std::size_t index) const;
        const std::vector<Mesh>& getMeshes() const;

        std::size_t addInstance(const Instance& instance);
        const Instance& getInstance(std::size_t index) const;
        const std::vector<Instance>& getInstances() const;

    private:
        std::vector<Mesh> m_meshes;
        std::vector<Instance> m_instances;
    };

}
#endif