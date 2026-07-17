#pragma once

#include "device.hpp"
#include "buffer.hpp"

#include <glm/glm.hpp>


struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};



class Descriptor
{

public:

    Descriptor(Device& device);

    ~Descriptor();



    void createLayout();

    void createPool();

    void createSet(
        Buffer& uniformBuffer
    );



    VkDescriptorSetLayout* getLayout()
    {
        return &descriptorSetLayout;
    }


    const VkDescriptorSet& getSet() const
    {
        return descriptorSet;
    }



private:

    Device& device;


    VkDescriptorSetLayout descriptorSetLayout =
        VK_NULL_HANDLE;


    VkDescriptorPool descriptorPool =
        VK_NULL_HANDLE;


    VkDescriptorSet descriptorSet =
        VK_NULL_HANDLE;

};