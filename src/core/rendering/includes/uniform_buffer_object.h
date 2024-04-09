#pragma once

#include <glm/glm.hpp>


namespace Engine::Rendering
{
    struct UniformBufferObject
    {
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };
}