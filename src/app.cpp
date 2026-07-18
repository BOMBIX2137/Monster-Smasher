#include"app.hpp"

App::App()
{
	renderer.setCamera(&camera);
	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	lastTime = glfwGetTime();
}

App::~App()
{

}

void App::run()
{
	while (!window.windowShouldClose()) {
		glfwPollEvents();

		float now = glfwGetTime();
		float dt = now - lastTime;
		lastTime = now;

		renderer.handleInput(window.getWindow(), dt);
		camera.updatePhysics(dt);
		renderer.drawFrame();
	}
	vkDeviceWaitIdle(device.device());
}
