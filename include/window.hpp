#pragma once
#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

#include<string>
class Window {

public:
	Window(int w, int h, const std::string& name);
	~Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	
	bool windowShouldClose() const { return glfwWindowShouldClose(window); }
	GLFWwindow* getWindow() const { return window; }
	void createSurface(VkInstance instance, VkSurfaceKHR *surface);
	bool wasWindowResized() const { return framebufferResized; }
	void resetWindowResizedFlag() { framebufferResized = false; }

private:
	void initWindow();
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	int width, height;
	std::string windowName;

	GLFWwindow* window = nullptr;
	bool framebufferResized = false;

};