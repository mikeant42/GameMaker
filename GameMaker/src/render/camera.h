#pragma once


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "../core/node.h"

class Node;

class Camera : public Node
{
public:
	Camera();
	~Camera();

	void Render(const Camera *cam);
	void Update(float deltaTime);
	void Input(const InputData &data, float deltaTime);

	inline glm::vec3 GetCamFront() {
		return cameraFront;
	}

	inline glm::vec3 GetCamUp() {
		return cameraUp;
	}

	inline GLfloat GetFOV() {
		return fov;
	}

private:
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;
	GLfloat fov = 45.0f;

	float lastX, lastY = 1.0f;
};

