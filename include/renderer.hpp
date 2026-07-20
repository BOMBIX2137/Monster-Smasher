#pragma once

#include "device.hpp"
#include "swapChain.hpp"
#include "graphicsPipeline.hpp"
#include "buffer.hpp"
#include "descriptor.hpp"
#include"camera.hpp"
#include"texture.hpp"
#include"modelPipeline.hpp"
#include"model.hpp"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <memory>


constexpr int MAX_FRAMES_IN_FLIGHT = 2;


const std::vector<Vertex> vertices = {

    {{-0.5f,-0.5f, 0.5f},{1,0,0}},
    {{ 0.5f,-0.5f, 0.5f},{0,1,0}},
    {{ 0.5f, 0.5f, 0.5f},{0,0,1}},
    {{-0.5f, 0.5f, 0.5f},{1,1,0}},

    {{-0.5f,-0.5f,-0.5f},{1,0,1}},
    {{ 0.5f,-0.5f,-0.5f},{0,1,1}},
    {{ 0.5f, 0.5f,-0.5f},{1,1,1}},
    {{-0.5f, 0.5f,-0.5f},{0,0,0}}
};


const std::vector<uint16_t> indices = {

    0,1,2,
    2,3,0,

    6,5,4,
    4,7,6,

    4,0,3,
    3,7,4,

    1,5,6,
    6,2,1,

    3,2,6,
    6,7,3,

    4,5,1,
    1,0,4
};

class Renderer {

public:

    Renderer(
        Window& window,
        Device& device,
        SwapChain& swapChain,
        GraphicsPipeline& graphicsPipeline,
        Descriptor& descriptor
    );

    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void drawFrame();

    void setCamera(Camera* cam) { camera = cam; }
    void handleInput(GLFWwindow* window, float dt);

private:

    void createCommandBuffers();

    void recordCommandBuffer(
        VkCommandBuffer commandBuffer,
        uint32_t imageIndex
    );


    void createSyncObjects();

    void createVertexBuffer();

    void createIndexBuffer();

    void updateUniformBuffer();

    void createWeaponDescriptorSet();



private:

    Camera* camera = VK_NULL_HANDLE;
    float lastX = 0, lastY = 0;
    bool firstMouse = true;

    Window& window;

    Device& device;

    SwapChain& swapChain;

    GraphicsPipeline& graphicsPipeline;

    Descriptor& descriptor;



    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkCommandBuffer> commandBuffers;
    uint32_t currentFrame = 0;


    //cube
    std::unique_ptr<Buffer> vertexBuffer;
    std::unique_ptr<Buffer> indexBuffer;
    std::unique_ptr<Texture> texture;
    std::unique_ptr<Buffer> uniformBuffers[MAX_FRAMES_IN_FLIGHT];

    //weapon
    std::unique_ptr<ModelPipeline> weaponPipeline;
    std::unique_ptr<Model> weapon;
    std::unique_ptr<Texture> weaponTexture;
    VkDescriptorSet weaponDescriptorSet = VK_NULL_HANDLE;
    VkDescriptorSetLayout weaponSamplerLayout = VK_NULL_HANDLE;
    VkDescriptorPool weaponDescriptorPool = VK_NULL_HANDLE;
};