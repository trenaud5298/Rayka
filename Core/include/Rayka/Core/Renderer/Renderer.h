// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, Tyler Renaud

#ifndef RAYKA_CORE_RENDERER_H
#define RAYKA_CORE_RENDERER_H

// Rayka Includes
#include <Rayka/Core/Export.h>

// C++ Includes

namespace Rayka {
    class Scene;

    class RAYKA_CORE_EXPORT Renderer {
    public:
        virtual ~Renderer() = default;
        virtual void render(const Scene& scene) = 0;
    protected:
        Renderer() = default;
    };


}
#endif