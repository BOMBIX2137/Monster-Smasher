#pragma once

#include "device.hpp"
#include"window.hpp"

#include<vector>

class SwapChain {
public:
	SwapChain(Device& device, Window& window);
	~SwapChain();

	SwapChain(const SwapChain&) = delete;
	SwapChain& operator = (const SwapChain&) = delete;

private:
	void createSwapChain();
	void createImageViews();
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);


	Window& window;
	Device& device;

	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;

	std::vector<VkImage> swapChainImages;

	VkFormat swapChainImageFormat = VK_FORMAT_UNDEFINED;
	VkExtent2D swapChainExtent{};

	std::vector<VkImageView> swapChainImageViews;
};