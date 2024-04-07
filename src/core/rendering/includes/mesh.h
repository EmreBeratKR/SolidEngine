#pragma once

#include <vector>


#include "vertex.h"
#include "vulkan_buffer.hpp"


namespace Engine::Rendering
{
	struct Mesh
	{
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};
}