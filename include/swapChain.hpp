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

	VkRenderPass getRenderPass() const { return renderPass; }
	VkFramebuffer getFramebuffer(uint32_t index) const { return swapChainFramebuffers[index]; }
	VkExtent2D getExtent() const { return swapChainExtent; }
	VkFormat getImageFormat() const { return swapChainImageFormat; }
	VkSwapchainKHR getSwapChain() const { return m_swapChain; }

private:
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createFrameBuffers();

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
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass;
};