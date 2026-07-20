#include "model.hpp"

#include<tiny_obj_loader.h>

#include<unordered_map>
#include<stdexcept>
#include<iostream>

namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			size_t seed = 0;
			auto hashCombine = [&seed](auto v) {
				seed ^= std::hash<decltype(v)>{}(v) +0x9e3779b9 + (seed << 6) + (seed >> 2);
			};
			hashCombine(vertex.pos.x); hashCombine(vertex.pos.y); hashCombine(vertex.pos.z);
			hashCombine(vertex.texCoord.x);  hashCombine(vertex.texCoord.y);
			hashCombine(vertex.normal.x); hashCombine(vertex.normal.y); hashCombine(vertex.normal.z);
			return seed;
		}
	};
}


Model::Model(Device& device, const std::string& filepath) : device{device}
{
	loadModel(filepath);
}

void Model::bind(VkCommandBuffer commandBuffer)
{
	VkBuffer buffers[] = { vertexBuffer->getBuffer() };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
	if (hasIndexBuffer) {
		vkCmdBindIndexBuffer(commandBuffer, indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
	}
}

void Model::draw(VkCommandBuffer commandBuffer)
{
	if (hasIndexBuffer) {
		vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
	}
	else {
		vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
	}
}

void Model::loadModel(const std::string& filepath)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str())) {
		throw std::runtime_error(warn + err);
	}

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::unordered_map<Vertex, uint32_t> uniqueVertices{};

	size_t totalIndices = 0;

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			totalIndices++;
			Vertex vertex{};

			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2],
			};

			if (index.normal_index >= 0) {
				vertex.normal = {
					attrib.normals[3 * index.normal_index + 0],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2],
				};
			}

			if (index.texcoord_index >= 0) {
				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1],
				};
			}

			vertex.color = { 1.0f, 1.0f, 1.0f };

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}
			indices.push_back(uniqueVertices[vertex]);
		}
	}
	std::cout << "Model load: " << filepath << std::endl;
	std::cout << "  Total indices (before dedup): " << totalIndices << std::endl;
	std::cout << "  Unique vertices (after dedup): " << vertices.size() << std::endl;
	std::cout << "  Final indices: " << indices.size() << std::endl;
	std::cout << "  Dedup ratio: " << (float)totalIndices / vertices.size() << "x" << std::endl;
	createVertexBuffers(vertices);
	createIndexBuffers(indices);
}

void Model::createVertexBuffers(const std::vector<Vertex>& vertices)
{
	vertexCount = static_cast<uint32_t>(vertices.size());
	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
	
	Buffer stagingBuffer(
		device, bufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VMA_MEMORY_USAGE_CPU_ONLY
	);
	stagingBuffer.writeToBuffer(vertices.data(), bufferSize);

	vertexBuffer = std::make_unique<Buffer>(device, bufferSize,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VMA_MEMORY_USAGE_GPU_ONLY
	);

	device.copyBuffer(stagingBuffer.getBuffer(), vertexBuffer->getBuffer(), bufferSize);
}

void Model::createIndexBuffers(const std::vector<uint32_t>& indices)
{
	indexCount = static_cast<uint32_t>(indices.size());
	hasIndexBuffer = indexCount > 0;

	std::cout << "Creating index buffer: " << indexCount << " indices" << std::endl;


	VkDeviceSize bufferSize = sizeof(uint32_t) * indexCount;

	Buffer stagingBuffer(
		device, bufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VMA_MEMORY_USAGE_CPU_ONLY
	);
	stagingBuffer.writeToBuffer(indices.data(), bufferSize);

	indexBuffer = std::make_unique<Buffer>(
		device, bufferSize,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
		VMA_MEMORY_USAGE_GPU_ONLY
	);
	device.copyBuffer(stagingBuffer.getBuffer(), indexBuffer->getBuffer(), bufferSize);
}
