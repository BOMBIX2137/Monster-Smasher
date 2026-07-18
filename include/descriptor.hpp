#pragma once

#include "device.hpp"
#include "buffer.hpp"

#include <glm/glm.hpp>
#include<array>


struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

class Descriptor
{

public:
    static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    Descriptor(Device& device);

    ~Descriptor();

    void createLayout();

    void createPool();

    VkDescriptorSet createSet(
        Buffer& uniformBuffer
    );

    VkDescriptorSetLayout* getLayout()
    {
        return &descriptorSetLayout;
    }

    const VkDescriptorSet& getSet(size_t frameIndex) const
    {
        return descriptorSets[frameIndex];
    }

private:

    Device& device;


    VkDescriptorSetLayout descriptorSetLayout =
        VK_NULL_HANDLE;


    VkDescriptorPool descriptorPool =
        VK_NULL_HANDLE;


    std::array<VkDescriptorSet, MAX_FRAMES_IN_FLIGHT> descriptorSets = {};
    size_t createdSets = 0;
};