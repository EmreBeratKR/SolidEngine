#pragma once

#include <vector>


#include "fwd.h"


namespace Engine::Rendering
{
	struct Mesh
	{
		VertexBuffer* vertexBuffer;
		IndexBuffer* indexBuffer;
		

		Mesh();
		~Mesh();
	};
}