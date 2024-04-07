#include <iostream>


#include "vulkan_graphic_engine.h"
#include "push_constant_data.h"
#include "mesh_renderer.h"


namespace Engine::Components
{
	void MeshRenderer::OnRender()
	{
		auto vulkan = Rendering::VulkanGraphicEngine::GetInstance();
		auto transform = getTransform();
		auto vertexBuffer = mesh->vertexBuffer;
		auto indexBuffer = mesh->indexBuffer;

		vulkan->setVertexBuffer(vertexBuffer.GetVkBuffer());
		vulkan->setIndexBuffer(indexBuffer.GetVkBuffer(), indexBuffer.GetSize());

		Rendering::PushConstantData push;
		push.transform = transform->getMatrix();

		vulkan->setPushConstant(push);
		vulkan->drawFrame();
	}

	void MeshRenderer::setMesh(Rendering::Mesh* mesh)
	{
		this->mesh = mesh;
	}
}