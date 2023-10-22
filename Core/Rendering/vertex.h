#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>


namespace Engine::Rendering
{
	struct Vertex
	{
		glm::vec2 position;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
	};
}