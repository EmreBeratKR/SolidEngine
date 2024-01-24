#pragma once

#include "glm/glm.hpp"

namespace Engine::Rendering
{
    struct PushConstantData
    {
        glm::mat4 transform;
    };
}