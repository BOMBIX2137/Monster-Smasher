#pragma once
#include"device.hpp"
#include"swapChain.hpp"
#include"graphicsPipeline.hpp"

class Renderer {
public:
	Renderer(Window& window,
		Device& device,
		SwapChain& swapChain,
		GraphicsPipeline& graphicsPipeline);
	~Renderer();

	void drawFrame();


private:
	void createCommandBuffer();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void createSyncObjects();



	Window& window;
	Device& device;
	SwapChain& swapChain;
	GraphicsPipeline& graphicsPipeline;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;

	VkCommandBuffer commandBuffer;
};