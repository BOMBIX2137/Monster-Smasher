#pragma once

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

enum class MovementDir {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera {
public:
	Camera(glm::vec3 pos = { 2.0f, 2.0f, 3.0f }, float yaw = -90.0f, float pitch = 0.0f);

	glm::mat4 getView();
	glm::mat4 getProj(float aspect, float nearPlane = 0.1f, float farPlane = 100.0f) const;

	void move(MovementDir dir, float dt);
	void rotate(float dx, float dy);
	void zoom(float offset);

	void jump();
	void updatePhysics(float dt);

	glm::vec3 getPos() const { return position; }
	float getZoom() const { return fov; }

private:
	void updateVectors();

	glm::vec3 position;
	glm::vec3 front{ 0.0f, 0.0f, -1.0f };
	glm::vec3 up{ 0.0f, 1.0f, 0.0f };
	glm::vec3 right;
	glm::vec3 worldUp{ 0.0f, 1.0f, 0.0f };

	float yaw;
	float pitch;
	float speed = 2.5f;
	float sensivity = 0.1f;
	float fov = 45.0f;

	float velocityY = 0.0f;
	float gravity = -25.0f;
	float jumpForce = 10.0f;
	float floorY = 0.0f;
	float eyeHeight = 1.8f;
	bool grounded = true;
};