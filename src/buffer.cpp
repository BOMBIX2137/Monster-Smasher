#include "buffer.hpp"
#include<stdexcept>

Buffer::Buffer(Device& device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) : device{ device }
{
    device.createBuffer(size, usage, properties, buffer, memory);
}

Buffer::~Buffer()
{
    vkDestroyBuffer(device.device(), buffer, nullptr);
    vkFreeMemory(device.device(), memory, nullptr);
}

void Buffer::map(VkDeviceSize size, VkDeviceSize offset)
{
    vkMapMemory(device.device(), memory, offset, size, 0, &mapped);
}

void Buffer::unmap()
{
    if (mapped) {
        vkUnmapMemory(device.device(), memory);
        mapped = nullptr;
    }
}

void Buffer::writeToBuffer(const void* data, VkDeviceSize size)
{
    map();
    memcpy(mapped, data, size);
    unmap();
}

void Buffer::bind()
{
    vkBindBufferMemory(device.device(), buffer, memory, 0);
}

