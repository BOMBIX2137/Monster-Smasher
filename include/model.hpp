#pragma once
#include"device.hpp"
#include"buffer.hpp"
#include"vertex.hpp"

#include<memory>
#include<vector>
#include<string>

class Model {
public:

	Model(Device& device, const std::string& filepath);
	~Model() = default;

	Model(const Model&) = delete;
	Model& operator = (const Model&) = delete;

	void bind(VkCommandBuffer commandBuffer);
	void draw(VkCommandBuffer commandBuffer);

private:
	void loadModel(const std::string& filepath);
	void createVertexBuffers(const std::vector<Vertex>& vertices);
	void createIndexBuffers(const std::vector<uint32_t>& indices);

	Device& device;

	std::unique_ptr<Buffer> vertexBuffer;
	uint32_t vertexCount;

	std::unique_ptr<Buffer> indexBuffer;
	uint32_t indexCount;
	bool hasIndexBuffer = false;
};