#pragma once


#include <vulkan/vulkan.h>
#include <vector>


#include "fwd.h"


namespace Engine::Rendering
{
    template<typename T>
    class VulkanBuffer
    {
    protected:
        VkBuffer buffer;
        VkDeviceMemory memory;
        std::vector<T> items;

    public:
        VkBuffer GetVkBuffer() { return buffer; }
        std::size_t GetSize() { return items.size(); }
        void AddItem(T item) { items.push_back(item); }

    protected:
        void AllocateWithUsageFlag(VkBufferUsageFlagBits usageFlag, VkDeviceSize bufferSize);
    };


    class VertexBuffer : public VulkanBuffer<Vertex> 
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void Allocate();
    };

    class IndexBuffer : public VulkanBuffer<uint32_t> 
    {
    public:
        IndexBuffer();
        ~IndexBuffer();

        void Allocate();
    };
}