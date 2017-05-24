#include "camera.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "light/light.h"

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

void Camera::CreateMatrices(int width, int height) {
	// Create transformations
	view = glm::mat4();
	view = glm::lookAt(GetTransform()->GetPosition(), GetTransform()->GetPosition()
		+ GetCamFront(), GetCamUp());

	projection = glm::mat4();
	projection = glm::perspective(45.0f, GLfloat(width / height), 0.1f, 10000.0f);
}

void Camera::Render(Camera *cam, std::vector<Light> lights) {
	Node::Render(cam, lights);
}

void Camera::Update(float deltaTime) {
	Node::Update(deltaTime);
}

void Camera::Input(const InputData &data, float deltaTime) {
	Node::Input(data, deltaTime);
	GLfloat cameraSpeed = 5 * deltaTime;
	if (data.keys[GLFW_KEY_W]) {
		transform.SetPosition(transform.GetPosition() + cameraSpeed * cameraFront);
	}
	if (data.keys[GLFW_KEY_S])
		transform.SetPosition(transform.GetPosition() - cameraSpeed * cameraFront);
	if (data.keys[GLFW_KEY_A])
		transform.SetPosition(transform.GetPosition() - glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
	if (data.keys[GLFW_KEY_D])
		transform.SetPosition(transform.GetPosition() + glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);

	double xpos = data.mousePosX;
	double ypos = data.mousePosY;

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

}


