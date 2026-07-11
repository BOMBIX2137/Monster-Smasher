#pragma once
#include"window.hpp"

#include<vector>

class Device {
public:
	Device();
	~Device();

	Device(const Device&) = delete;
	Device& operator = (const Device&) = delete;

private:
	void createInstance();
	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void setupDebugMessenger();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice;
};