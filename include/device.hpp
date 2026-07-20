#pragma once
#include"window.hpp"
#include"vk_mem_alloc.h"

#include<vector>
#include<optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class Device {
public:
	Device(Window &window);
	~Device();

	Device(const Device&) = delete;
	Device& operator = (const Device&) = delete;

	SwapChainSupportDetails getSwapChainSupport() const { return querySwapChainSupport(physicalDevice); }
	VkSurfaceKHR getSurface() const { return surface; }
	QueueFamilyIndices findPhysicalQueueFamilies() const { return findQueueFamilies(physicalDevice); }
	VkDevice device() const { return m_device; }
	VkCommandPool getCommandPool() const { return commandPool; }
	VkQueue getGraphicsQueue() const { return graphicsQueue; }
	VkQueue getPresentQueue() const { return presentQueue; }
	VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }
	VmaAllocator getAllocator() const { return allocator; }

	//void createBuffer(VkDeviceSize size,
	//	VkBufferUsageFlags usage,
	//	VkMemoryPropertyFlags properties,
	//	VkBuffer& buffer,
	//	VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

private:
	void createInstance();
	void setupDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createCommandPool();
	void createAllocator();

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
	bool checkDeviceExtensionsSupported(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	Window& window;

	VkInstance instance = VK_NULL_HANDLE;
	VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentQueue = VK_NULL_HANDLE;
	VkSurfaceKHR surface = VK_NULL_HANDLE;

	VkCommandPool commandPool = VK_NULL_HANDLE;
	VmaAllocator allocator = VK_NULL_HANDLE;
};