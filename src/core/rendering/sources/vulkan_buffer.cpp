#include <vector>
#include <string>


#include "vertex.h"
#include "vulkan_buffer.h"
#include "vulkan_graphic_engine.h"


namespace Engine::Rendering
{
    template<typename T>
    void VulkanBuffer<T>::AllocateWithUsageFlag(VkBufferUsageFlagBits usageFlag, VkDeviceSize bufferSize)
    {
        VulkanGraphicEngine* vulkan = VulkanGraphicEngine::GetInstance();
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        VkDevice device = vulkan->GetLogicalDevice();

        vulkan->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, items.data(), (size_t)bufferSize);
        vkUnmapMemory(device, stagingBufferMemory);

        vulkan->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | usageFlag, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffer, memory);
        vulkan->copyBuffer(stagingBuffer, buffer, bufferSize);

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);
    }


    void VertexBuffer::Allocate()
    {
        auto bufferSize = sizeof(Vertex) * GetSize();

        AllocateWithUsageFlag(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, bufferSize);
    }


    void IndexBuffer::Allocate()
    {
        auto bufferSize = sizeof(uint32_t) * GetSize();

        AllocateWithUsageFlag(VK_BUFFER_USAGE_INDEX_BUFFER_BIT, bufferSize);
    }
}