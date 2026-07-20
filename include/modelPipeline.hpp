#pragma once
#include"device.hpp"
#include"swapChain.hpp"

class ModelPipeline {
public:
	ModelPipeline(Device& device, SwapChain& swapChain);
	~ModelPipeline();

	VkPipeline getPipeline() const { return graphicsPipeline; }
	VkPipelineLayout getLayout() const { return pipelineLayout; }

	ModelPipeline(const ModelPipeline&) = delete;
	ModelPipeline& operator=(const ModelPipeline&) = delete;

private:
	void createGraphicsPipeline();
	VkShaderModule createShaderModule(const std::vector<char>& code);
	std::vector<char> readFile(const std::string& filename);

	Device& device;
	SwapChain& swapChain;
	VkPipeline graphicsPipeline;
	VkPipelineLayout pipelineLayout;
};