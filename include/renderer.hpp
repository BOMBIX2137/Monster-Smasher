#pragma once
#include"device.hpp"
#include"swapChain.hpp"
#include"graphicsPipeline.hpp"
#include"buffer.hpp"

#include<memory>

constexpr int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<Vertex> vertices = {
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0
};

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
	void createVertexBuffer();
	void createIndexBuffer();



	Window& window;
	Device& device;
	SwapChain& swapChain;
	GraphicsPipeline& graphicsPipeline;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	std::vector<VkCommandBuffer> commandBuffers;
	uint32_t currentFrame = 0;

	std::unique_ptr<Buffer> vertexBuffer;
	std::unique_ptr<Buffer> indexBuffer;
};