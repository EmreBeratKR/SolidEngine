#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>


namespace Engine::Rendering
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texCoord;

		static VkVertexInputBindingDescription getBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
	};
}