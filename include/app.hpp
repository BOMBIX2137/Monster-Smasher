#pragma once
#include"renderer.hpp"

class App {
public:
	static constexpr int WIDTH = 800;
	static constexpr int HEIGHT = 600;

	App();
	~App();
	void run();

	App(const App&) = delete;
	App& operator = (const App&) = delete;

private:
	Window window{ WIDTH, HEIGHT, "MONSTER SMASHER" };
	Device device{window};
	SwapChain swapChain{ device, window };
	Descriptor descriptor{ device };
	GraphicsPipeline pipeline{ device, swapChain,descriptor };
	Renderer renderer{ window, device, swapChain, pipeline, descriptor };
};