#pragma once

#include <vector>


#include "vertex.h"


namespace Engine::Rendering
{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};
}