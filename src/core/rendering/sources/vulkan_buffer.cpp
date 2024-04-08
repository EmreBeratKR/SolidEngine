#include <vector>
#include <string>


#include "vertex.h"
#include "vulkan_buffer.h"
#include "vulkan_graphic_engine.h"


namespace Engine::Rendering
{
    template class VulkanBuffer<Vertex>;
    template class VulkanBuffer<uint32_t>;

    template<typename T>
    void VulkanBuffer<T>::AllocateWithUsageFlag(VkBufferUsageFlagBits usageFlag)
    {
        VulkanGraphicEngine* vulkan = VulkanGraphicEngine::GetInstance();
        VkDeviceSize bufferSize = this->bufferSize;
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
        bufferSize = sizeof(Vertex) * GetSize();;
        AllocateWithUsageFlag(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
    }


    void IndexBuffer::Allocate()
    {
        bufferSize = sizeof(uint32_t) * GetSize();
        AllocateWithUsageFlag(VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
    }
}