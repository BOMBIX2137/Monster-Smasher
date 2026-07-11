#include"app.hpp"

App::App()
{

}

App::~App()
{

}

void App::run()
{
	while (!window.windowShouldClose()) {
		glfwPollEvents();
	}
}
