#pragma once
#include"device.hpp"
#include"swapChain.hpp"
#include"graphicsPipeline.hpp"

constexpr int MAX_FRAMES_IN_FLIGHT = 2;

class Renderer {
public:
	Renderer(Window& window,
		Device& device,
		SwapChain& swapChain,
		GraphicsPipeline& graphicsPipeline);
	~Renderer();

	void drawFrame();

private:
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void createSyncObjects();



	Window& window;
	Device& device;
	SwapChain& swapChain;
	GraphicsPipeline& graphicsPipeline;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	std::vector<VkCommandBuffer> commandBuffers;
	uint32_t currentFrame = 0;

};