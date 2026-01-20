#ifndef RAYKA_CORE_INSTANCE_H
#define RAYKA_CORE_INSTANCE_H

// Rayka Includes
#include <Rayka/Core/Export.h>

// C++ Includes
#include <cstdint>


namespace Rayka {
    struct RAYKA_CORE_EXPORT Transform {
        float position[3] {0.0f, 0.0f, 0.0f};
        float scale[3]    {1.0f, 1.0f, 1.0f};
    };

    struct RAYKA_CORE_EXPORT Instance {
        std::size_t meshIndex;
        Transform transform;
    };
}

#endif