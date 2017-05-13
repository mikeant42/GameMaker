#pragma once

#include "../core/node.h"

class Camera : public Node
{
public:
	Camera();
	~Camera();

	void Render();
	void Update(float deltaTime);
	void Input(bool keys[], float deltaTime);

	inline glm::vec3 GetCamFront() {
		return cameraFront;
	}

	inline glm::vec3 GetCamUp() {
		return cameraUp;
	}

private:
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
};

