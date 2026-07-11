#pragma once
#include"device.hpp"

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
	Device device{};
};