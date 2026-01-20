// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, Tyler Renaud

#ifndef RAYKA_CORE_HOSTRENDERER_H
#define RAYKA_CORE_HOSTRENDERER_H

// Rayka Includes
#include <Rayka/Core/Export.h>
#include <Rayka/Core/Render/Renderer.h>

// C++ Includes

namespace Rayka {
    class Scene;

    class RAYKA_CORE_EXPORT HostRenderer : public Renderer {
    public:
        HostRenderer() = default;
        ~HostRenderer() override = default;
        void render(const Scene& scene) override;
    };

}
#endif