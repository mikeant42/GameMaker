#pragma once

#include <glm/glm.hpp>

struct PBRMaterial {
	glm::vec3 albedo = glm::vec3(0.5f, 0,0);
	float ao = 1.0f;
	float metallic = 0.3f;
	float roughness = 0.2f;
};