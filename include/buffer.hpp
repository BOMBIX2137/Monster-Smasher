#pragma once
#include "device.hpp"

#include<glm/glm.hpp>
#include<array>

class Buffer {
public:
	Buffer(Device& device,
		VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags properties
	);

	~Buffer();

	Buffer(const Buffer&) = delete;
	Buffer& operator=(const Buffer&) = delete;

	VkBuffer getBuffer() const { return buffer; }

	void map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
	void unmap();
	void writeToBuffer(const void* data, VkDeviceSize size);
	void bind();

private:

	Device& device;

	VkBuffer buffer{};
	VkDeviceMemory memory = VK_NULL_HANDLE;
	void* mapped = nullptr;
};