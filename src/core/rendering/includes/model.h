#pragma once

#include <vector>


#include "mesh.h"


namespace Engine::Rendering
{
	struct Model
	{
		std::vector<Mesh> meshes{};
	};
}