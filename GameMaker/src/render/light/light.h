#pragma once

#include <glm/glm.hpp>

class Light {
public:
	Light() {}
	~Light() {}

	inline void SetColor(const glm::vec3 &color) {
		_color = color;
	}

	inline glm::vec3 GetColor() {
		return _color;
	}

	inline void SetPosition(const glm::vec3 &pos) {
		_position = pos;
	}

	inline glm::vec3 GetPosition() {
		return _position;
	}

private:
	glm::vec3 _color = glm::vec3();
	glm::vec3 _position = glm::vec3();
};