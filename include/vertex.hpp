#pragma once

#include<array>
#include<glm/glm.hpp>
#include<vulkan/vulkan.h>

struct Vertex {

    glm::vec3 pos;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 texCoord;


    static VkVertexInputBindingDescription getBindingDescription();


    static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions();

    bool operator==(const Vertex& other) const {
        return pos == other.pos && color == other.color && normal == other.normal && texCoord == other.texCoord;
    }
};