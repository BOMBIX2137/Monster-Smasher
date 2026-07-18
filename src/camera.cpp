#include "camera.hpp"

#include<algorithm>

Camera::Camera(glm::vec3 pos, float yaw, float pitch) : position{pos}, yaw{yaw}, pitch{pitch}
{
	updateVectors();
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProj(float aspect, float nearPlane, float farPlane) const
{
	auto proj = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
	proj[1][1] *= -1;
	return proj;
}

void Camera::move(MovementDir dir, float dt)
{
	float v = speed * dt;
	glm::vec3 flatFront = glm::normalize(glm::vec3(front.x, 0, front.z));

	switch (dir) {
	case MovementDir::FORWARD: position += flatFront * v; break;
	case MovementDir::BACKWARD: position -= flatFront * v; break;
	case MovementDir::LEFT: position -= right * v; break;
	case MovementDir::RIGHT: position += right * v; break;
	}
}

void Camera::rotate(float dx, float dy)
{
	yaw += dx * sensivity;
	pitch += dy * sensivity;
	pitch = std::clamp(pitch, -89.0f, 89.0f);
	updateVectors();
}

void Camera::zoom(float offset)
{
	fov -= offset;
	fov = std::clamp(fov, 1.0f, 90.0f);
}

void Camera::jump()
{
	if (grounded) {
		velocityY = jumpForce;
		grounded = false;
	}
}

void Camera::updatePhysics(float dt)
{
	if (!grounded) {
		velocityY += gravity * dt;
		position.y += velocityY * dt;

		if (position.y <= floorY + eyeHeight) {
			position.y = floorY + eyeHeight;
			velocityY = 0.0f;
			grounded = true;
		}
	}
}

void Camera::updateVectors()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	glm::vec3 flatFront = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

	right = glm::normalize(glm::cross(flatFront, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
