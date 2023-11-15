#pragma once


#include "vertex.h"
#include <vector>


namespace Engine::Rendering
{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};
}