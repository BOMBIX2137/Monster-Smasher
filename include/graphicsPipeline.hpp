#pragma once
#include<vector>
#include<string>
#include "descriptor.hpp"
#include"device.hpp"
#include"swapChain.hpp"
#include<glm/glm.hpp>
#include<array>


struct Vertex {

    glm::vec3 pos;
    glm::vec3 color;


    static VkVertexInputBindingDescription getBindingDescription()
    {
        VkVertexInputBindingDescription binding{};

        binding.binding = 0;
        binding.stride = sizeof(Vertex);
        binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return binding;
    }


    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 2> attributes{};


        attributes[0].binding = 0;
        attributes[0].location = 0;
        attributes[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributes[0].offset = offsetof(Vertex, pos);


        attributes[1].binding = 0;
        attributes[1].location = 1;
        attributes[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributes[1].offset = offsetof(Vertex, color);


        return attributes;
    }
};

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