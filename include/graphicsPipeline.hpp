#pragma once
#include<vector>
#include<string>

#include"device.hpp"
#include"swapChain.hpp"

class GraphicsPipeline {

public:
	GraphicsPipeline(Device& device, SwapChain& swapChain);
	~GraphicsPipeline();

	GraphicsPipeline(const GraphicsPipeline&) = delete;
	GraphicsPipeline& operator = (const GraphicsPipeline&) = delete;

	VkPipeline getPipeline() const { return graphicsPipeline; }
	VkPipelineLayout getPipelineLayout() const { return pipelineLayout; }

private:
	void createGraphicsPipeline();
	std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	Device& device;
	SwapChain& swapChain;
	
	VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
	VkPipeline graphicsPipeline = VK_NULL_HANDLE;
};