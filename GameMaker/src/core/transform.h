#pragma once

#include <glm/glm.hpp>

struct Transform {
public:
	void SetPosition(const glm::vec3 &pos);
	glm::vec3 GetPosition();

	void SetRotation(const glm::vec3 &rot);
	glm::vec3 GetRotation();

	void SetScale(float scale);
	float GetScale();
private:
	glm::vec3 position = glm::vec3(0,0,0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	float scale = 1;
};

inline void Transform::SetPosition(const glm::vec3 &pos) {
	position = pos;
}

inline glm::vec3 Transform::GetPosition() {
	return position;
}

inline void Transform::SetRotation(const glm::vec3 &rot) {
	rotation = rot;
}

inline glm::vec3 Transform::GetRotation() {
	return rotation;
}

inline void Transform::SetScale(float sc) {
	scale = sc;
}

inline float Transform::GetScale() {
	return scale;
}