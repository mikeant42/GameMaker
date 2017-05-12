#pragma once

#include <glm/glm.hpp>

class Transform 
{
public:
	Transform() {
		position = glm::vec3();
		rotation = glm::vec3();
		scale = 1;
	}

	~Transform() {

	}

	void SetPosition(glm::vec3 pos) {
		position = pos;
	}

	glm::vec3 GetPosition() {
		return position;
	}

	void SetRotation(glm::vec3 rot) {
		rotation = rot;
	}

	glm::vec3 GetRotation() {
		return rotation;
	}

	void SetScale(float scal) {
		scale = scal;
	}

	float GetScale() {
		return scale;
	}

private:
	glm::vec3 position;
	glm::vec3 rotation;
	float scale;
};