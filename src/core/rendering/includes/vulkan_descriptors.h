#pragma once

#define GLFW_INCLUDE_VULKAN


#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>


namespace Engine::Rendering
{
    class VulkanDescriptorSetLayout
    {
    public:
        class Builder
        {
        public:
            Builder(VkDevice& device) : device{device} {}

            Builder& AddBinding(uint32_t binding, VkDescriptorType descriptorType, VkShaderStageFlags stageFlags, uint32_t count = 1);
            VulkanDescriptorSetLayout* Build() const;


        private:
            VkDevice& device;
            std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
        };


        VulkanDescriptorSetLayout(VkDevice& device, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
        ~VulkanDescriptorSetLayout();


        VkDescriptorSetLayout* GetDescriptorSetLayout() { return &descriptorSetLayout; }


    private:
        VkDevice& device;
        VkDescriptorSetLayout descriptorSetLayout;
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings;


        friend class VulkanDescriptorWriter;
    };


    class VulkanDescriptorPool
    {
    public:
        class Builder
        {
            public:
                Builder(VkDevice& device) : device{device} {}

                Builder& AddPoolSize(VkDescriptorType descriptorType, uint32_t count);
                Builder& SetPoolFlags(VkDescriptorPoolCreateFlags flags);
                Builder& SetMaxSets(uint32_t count);
                VulkanDescriptorPool* Build() const;


            private:
                VkDevice& device;
                std::vector<VkDescriptorPoolSize> poolSizes{};
                uint32_t maxSets = 1000;
                VkDescriptorPoolCreateFlags poolFlags = 0;
        };


        VulkanDescriptorPool(VkDevice& device, uint32_t maxSets, VkDescriptorPoolCreateFlags poolFlags, const std::vector<VkDescriptorPoolSize>& poolSizes);
        ~VulkanDescriptorPool();


        VkDescriptorPool GetDescriptorPool() const { return descriptorPool; }
        bool AllocateDescriptor(const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet& descriptor) const;
        void FreeDescriptors(std::vector<VkDescriptorSet>& descriptors) const;
        void ResetPool();

    private:
        VkDevice& device;
        VkDescriptorPool descriptorPool;


        friend class VulkanDescriptorWriter;
    };


    class VulkanDescriptorWriter 
    {
    public:
        VulkanDescriptorWriter(VulkanDescriptorSetLayout& setLayout, VulkanDescriptorPool& pool) : setLayout{setLayout}, pool{pool} {}

        VulkanDescriptorWriter& WriteBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo);
        VulkanDescriptorWriter& WriteImage(uint32_t binding, VkDescriptorImageInfo* imageInfo);

        bool Build(VkDescriptorSet& set);
        void Overwrite(VkDescriptorSet& set);

    private:
        VulkanDescriptorSetLayout& setLayout;
        VulkanDescriptorPool& pool;
        std::vector<VkWriteDescriptorSet> writes;
    };
}