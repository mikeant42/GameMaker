#include "camera.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

Camera::Camera() : Node()
{
	//__super::Node(); 2 fancy 4 u
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	transform.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
}


Camera::~Camera()
{
}

void Camera::Render() {

}

void Camera::Update(float deltaTime) {
}

void Camera::Input(bool keys[], float deltaTime) {
	GLfloat cameraSpeed = 5 * deltaTime;
	if (keys[GLFW_KEY_W]) {
		transform.SetPosition(transform.GetPosition() + cameraSpeed * cameraFront);
	}
	if (keys[GLFW_KEY_S])
		transform.SetPosition(transform.GetPosition() - cameraSpeed * cameraFront);
	if (keys[GLFW_KEY_A])
		transform.SetPosition(transform.GetPosition() - glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
	if (keys[GLFW_KEY_D])
		transform.SetPosition(transform.GetPosition() + glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);

}


