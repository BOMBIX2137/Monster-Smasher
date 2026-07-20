#pragma once
#include"device.hpp"

#include<string>

class Texture {
public:
	Texture(Device& device, const std::string& filepath);
	~Texture();

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	VkImageView getImageView() const { return imageView; }
	VkSampler getSampler() const { return sampler; }
	VkDescriptorImageInfo descriptorInfo() const;

private:
	void createTextureImage(const std::string& filepath);
	void createTextureImageView();
	void createTextureSampler();

	Device& device;
	
	VkImage image = VK_NULL_HANDLE;
	VmaAllocation allocation = VK_NULL_HANDLE;
	VkImageView imageView = VK_NULL_HANDLE;
	VkSampler sampler = VK_NULL_HANDLE;

	int width = 0, height = 0, channels = 0;
};