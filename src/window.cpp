#include "window.hpp"
#include<stdexcept>
#include<iostream>

Window::Window(int w, int h, const std::string& name) : width{w}, height{h}, windowName{name}
{
	initWindow();
}

Window::~Window()
{
	std::cout << "window destructor" << std::endl;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::createSurface(VkInstance instance, VkSurfaceKHR *surface)
{
	if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

void Window::initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
	app->width = width;
	app->height = height;
}
