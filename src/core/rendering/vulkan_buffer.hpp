#pragma once


#define GLFW_INCLUDE_VULKAN


#include <GLFW/glfw3.h>
#include <vector>


#include "vulkan_graphic_engine.h"


namespace Engine::Rendering
{
    template<typename T>
    class VulkanBuffer
    {
        private:
            VkBuffer buffer;
            VkDeviceMemory memory;
            std::vector<T> items;


        public:
            VkBuffer GetVkBuffer()
            {
                return buffer;
            }

            std::size_t GetSize()
            {
                return this->items.size();
            }

            void AddItem(T item)
            {
                this->items.push_back(item);
            }

            void AllocateWithUsageFlag(VkBufferUsageFlagBits usageFlag)
            {
                VulkanGraphicEngine* vulkan = VulkanGraphicEngine::GetInstance();
                VkDeviceSize bufferSize = sizeof(items[0]) * items.size();
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
    };

    class VertexBuffer : public VulkanBuffer<Vertex>
    {
    public:
        void Allocate()
        {
            AllocateWithUsageFlag(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
        }
    };

    class IndexBuffer : public VulkanBuffer<uint32_t>
    {
    public:
        void Allocate()
        {
            AllocateWithUsageFlag(VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
        }
    };
}