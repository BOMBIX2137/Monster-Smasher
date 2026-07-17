#include "buffer.hpp"

#include <cstring>
#include <stdexcept>


Buffer::Buffer(
    Device& device,
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    VmaMemoryUsage memoryUsage
)
    :
    device{ device }
{

    VkBufferCreateInfo bufferInfo{};

    bufferInfo.sType =
        VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;

    bufferInfo.size = size;

    bufferInfo.usage = usage;

    bufferInfo.sharingMode =
        VK_SHARING_MODE_EXCLUSIVE;



    VmaAllocationCreateInfo allocInfo{};

    allocInfo.usage = memoryUsage;



    if (
        vmaCreateBuffer(
            device.getAllocator(),
            &bufferInfo,
            &allocInfo,
            &buffer,
            &allocation,
            nullptr
        )
        != VK_SUCCESS
        )
    {
        throw std::runtime_error(
            "failed to create buffer"
        );
    }
}



Buffer::~Buffer()
{
    vmaDestroyBuffer(
        device.getAllocator(),
        buffer,
        allocation
    );
}



void Buffer::map(
    VkDeviceSize size,
    VkDeviceSize offset
)
{
    vmaMapMemory(
        device.getAllocator(),
        allocation,
        &mapped
    );
}



void Buffer::unmap()
{
    if (mapped)
    {
        vmaUnmapMemory(device.getAllocator(),allocation);
        mapped = nullptr;
    }
}

void Buffer::writeToBuffer(
    const void* data,
    VkDeviceSize size
)
{
    map();
    memcpy(mapped, data, size);
    unmap();
}