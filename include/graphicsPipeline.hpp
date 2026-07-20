#pragma once
#include "descriptor.hpp"
#include"device.hpp"
#include"swapChain.hpp"
#include"vertex.hpp"


#include<glm/glm.hpp>
#include<array>
#include<string>
#include<vector>

class GraphicsPipeline {

public:

    GraphicsPipeline(
        Device& device,
        SwapChain& swapChain,
        Descriptor& descriptor
    );

    ~GraphicsPipeline();

    GraphicsPipeline(const GraphicsPipeline&) = delete;
    GraphicsPipeline& operator=(const GraphicsPipeline&) = delete;


    VkPipeline getPipeline() const {
        return graphicsPipeline;
    }

    VkPipelineLayout getPipelineLayout() const {
        return pipelineLayout;
    }


private:

    void createGraphicsPipeline();

    std::vector<char> readFile(
        const std::string& filename
    );

    VkShaderModule createShaderModule(
        const std::vector<char>& code
    );


    Device& device;
    SwapChain& swapChain;
    Descriptor& descriptor;


    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline = VK_NULL_HANDLE;
};