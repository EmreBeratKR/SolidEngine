#pragma once


#include "component.h"
#include "../rendering/mesh.h"


namespace Engine::Components
{
	class MeshRenderer : public Component
	{
	public:
		virtual void OnRender();
		void setMesh(Rendering::Mesh* mesh);
	private:
		Rendering::Mesh* mesh;
	};
}