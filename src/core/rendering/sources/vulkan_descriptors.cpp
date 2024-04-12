#include "vulkan_descriptors.h"
#include "log.h"


namespace Engine::Rendering
{
#pragma region Descriptor Set Layout Builder
    VulkanDescriptorSetLayout::Builder& VulkanDescriptorSetLayout::Builder::AddBinding(
        uint32_t binding, 
        VkDescriptorType descriptorType, 
        VkShaderStageFlags stageFlags, 
        uint32_t count)
        {
            auto isValidBinding = bindings.count(binding) == 0;

            if (!isValidBinding)
            {
                Log::Error("Invalid binding!");
            }

            VkDescriptorSetLayoutBinding layoutBinding{};
            layoutBinding.binding = binding;
            layoutBinding.descriptorType = descriptorType;
            layoutBinding.descriptorCount = count;
            layoutBinding.stageFlags = stageFlags;

            bindings[binding] = layoutBinding;

            return *this;
        }
    
    VulkanDescriptorSetLayout* VulkanDescriptorSetLayout::Builder::Build() const
    {
        return new VulkanDescriptorSetLayout(device, bindings);
    }
#pragma endregion


#pragma region Descriptor Set Layout
    VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(
        VkDevice& device, 
        std::unordered_map<uint32_t, 
        VkDescriptorSetLayoutBinding> bindings) : device{device}, bindings{bindings}
    {
        std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings{};

        for (auto kv : bindings) 
        {
            setLayoutBindings.push_back(kv.second);
        }

        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
        descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutInfo.bindingCount = static_cast<uint32_t>(setLayoutBindings.size());
        descriptorSetLayoutInfo.pBindings = setLayoutBindings.data();

        auto result = vkCreateDescriptorSetLayout(device, &descriptorSetLayoutInfo, nullptr, &descriptorSetLayout);

        if (result != VK_SUCCESS) 
        {
            Log::ThrowVkResult("failed to create descriptor set layout!", result);
        }
    }

    VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout()
    {
        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    }
#pragma endregion


#pragma region Descriptor Pool Builder
    VulkanDescriptorPool::Builder& VulkanDescriptorPool::Builder::AddPoolSize(VkDescriptorType descriptorType, uint32_t count)
    {
        poolSizes.push_back({descriptorType, count});
        return *this;
    }

    VulkanDescriptorPool::Builder& VulkanDescriptorPool::Builder::SetPoolFlags(VkDescriptorPoolCreateFlags flags)
    {
        poolFlags = flags;
        return *this;
    }

    VulkanDescriptorPool::Builder& VulkanDescriptorPool::Builder::SetMaxSets(uint32_t count)
    {
        maxSets = count;
        return *this;
    }

    VulkanDescriptorPool* VulkanDescriptorPool::Builder::Build() const
    {
        return new VulkanDescriptorPool(device, maxSets, poolFlags, poolSizes);
    }
#pragma endregion


#pragma region Descriptor Pool
    VulkanDescriptorPool::VulkanDescriptorPool(
        VkDevice& device, 
        uint32_t maxSets, 
        VkDescriptorPoolCreateFlags poolFlags, 
        const std::vector<VkDescriptorPoolSize>& poolSizes) : device{device}
    {
        VkDescriptorPoolCreateInfo descriptorPoolInfo{};
        descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        descriptorPoolInfo.pPoolSizes = poolSizes.data();
        descriptorPoolInfo.maxSets = maxSets;
        descriptorPoolInfo.flags = poolFlags;

        auto result = vkCreateDescriptorPool(device, &descriptorPoolInfo, nullptr, &descriptorPool);

        if (result != VK_SUCCESS) 
        {
            Log::ThrowVkResult("failed to create descriptor pool!", result);
        }
    }

    VulkanDescriptorPool::~VulkanDescriptorPool()
    {
        vkDestroyDescriptorPool(device, descriptorPool, nullptr);
    }


    bool VulkanDescriptorPool::AllocateDescriptor(const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet& descriptor) const
    {
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.pSetLayouts = &descriptorSetLayout;
        allocInfo.descriptorSetCount = 1;

        if (vkAllocateDescriptorSets(device, &allocInfo, &descriptor) != VK_SUCCESS) 
        {
            return false;
        }

        return true;
    }

    void VulkanDescriptorPool::FreeDescriptors(std::vector<VkDescriptorSet> &descriptors) const
    {
        vkFreeDescriptorSets(device, descriptorPool, static_cast<uint32_t>(descriptors.size()), descriptors.data());
    }

    void VulkanDescriptorPool::ResetPool()
    {
        vkResetDescriptorPool(device, descriptorPool, 0);
    }
#pragma endregion


#pragma region Descriptor Writer
    VulkanDescriptorWriter& VulkanDescriptorWriter::WriteBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo)
    {
        auto isValidBinding = setLayout.bindings.count(binding) == 1;

        if (!isValidBinding)
        {
            Log::Error("Layout does not contain specified binding");
        }

        auto &bindingDescription = setLayout.bindings[binding];

        auto isBindingCountMatch = bindingDescription.descriptorCount == 1;

        if (!isBindingCountMatch)
        {
            Log::Error("Binding single descriptor info, but binding expects multiple");
        }

        VkWriteDescriptorSet write{};
        write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.dstBinding = binding;
        write.dstArrayElement = 0;
        write.descriptorType = bindingDescription.descriptorType;
        write.descriptorCount = 1;
        write.pBufferInfo = bufferInfo;

        writes.push_back(write);
        return *this;
    }

    VulkanDescriptorWriter& VulkanDescriptorWriter::WriteImage(uint32_t binding, VkDescriptorImageInfo* imageInfo)
    {
        auto isValidBinding = setLayout.bindings.count(binding) == 1;

        if (!isValidBinding)
        {
            Log::Error("Layout does not contain specified binding");
        }

        auto &bindingDescription = setLayout.bindings[binding];

        auto isBindingCountMatch = bindingDescription.descriptorCount == 1;

        if (!isBindingCountMatch)
        {
            Log::Error("Binding single descriptor info, but binding expects multiple");
        }

        VkWriteDescriptorSet write{};
        write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.dstBinding = binding;
        write.dstArrayElement = 0;
        write.descriptorType = bindingDescription.descriptorType;
        write.descriptorCount = 1;
        write.pImageInfo = imageInfo;

        writes.push_back(write);
        return *this;
    }

    void VulkanDescriptorWriter::UpdateWriteImage(uint32_t binding, VkDescriptorImageInfo* imageInfo, VkDescriptorSet& set)
    {
        auto isValidBinding = setLayout.bindings.count(binding) == 1;

        if (!isValidBinding)
        {
            Log::Error("Layout does not contain specified binding");
        }

        auto &bindingDescription = setLayout.bindings[binding];

        auto isBindingCountMatch = bindingDescription.descriptorCount == 1;

        if (!isBindingCountMatch)
        {
            Log::Error("Binding single descriptor info, but binding expects multiple");
        }

        writes[binding].pImageInfo = imageInfo;
        
        Overwrite(set);
    }

    VulkanDescriptorWriter* VulkanDescriptorWriter::Build(VkDescriptorSet& set)
    {
        bool success = pool.AllocateDescriptor(*setLayout.GetDescriptorSetLayout(), set);

        if (!success) return nullptr;

        Overwrite(set);
        return this;
    }

    void VulkanDescriptorWriter::Overwrite(VkDescriptorSet& set)
    {
        for (auto &write : writes) 
        {
            write.dstSet = set;
        }

        vkUpdateDescriptorSets(pool.device, writes.size(), writes.data(), 0, nullptr);
    }
#pragma endregion
}