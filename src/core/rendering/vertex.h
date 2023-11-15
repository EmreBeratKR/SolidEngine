#pragma once

#define GLM_ENABLE_EXPERIMENTAL


#include <glm/gtx/hash.hpp>
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

		bool operator==(const Vertex& other) const;
	};
}

namespace std
{
	template<> struct hash<Engine::Rendering::Vertex>
	{
		size_t operator()(Engine::Rendering::Vertex const& vertex) const
		{
			return ((hash<glm::vec3>()(vertex.position) ^
				(hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}