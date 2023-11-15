#pragma once

#include "mesh.h"
#include <vector>


namespace Engine::Rendering
{
	struct Model
	{
		std::vector<Mesh> meshes{};
	};
}