#include <iostream>


#include "vulkan_graphic_engine.h"
#include "push_constant_data.h"
#include "mesh_renderer.h"


namespace Engine::Components
{
	void MeshRenderer::OnRender()
	{
		auto transform = getTransform();
		auto vertexBuffer = mesh->vertexBuffer;
		auto indexBuffer = mesh->indexBuffer;

		Rendering::VulkanGraphicEngine::ms_Instance->setVertexBuffer(vertexBuffer.GetVkBuffer());
		Rendering::VulkanGraphicEngine::ms_Instance->setIndexBuffer(indexBuffer.GetVkBuffer(), indexBuffer.GetSize());

		Rendering::PushConstantData push;
		push.transform = transform->getMatrix();

		Rendering::VulkanGraphicEngine::ms_Instance->setPushConstant(push);
		Rendering::VulkanGraphicEngine::ms_Instance->drawFrame();
	}

	void MeshRenderer::setMesh(Rendering::Mesh* mesh)
	{
		this->mesh = mesh;
	}
}