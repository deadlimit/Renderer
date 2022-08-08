#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace EditorCamera {
	
	inline float pitch = 0;
	inline float yaw = -90.f;

	void Init(const glm::vec3&, const glm::vec3&, const glm::vec3&, const bool&);
	
	glm::mat4 GetViewMatrix();

	void Rotate();

	void Move(const glm::vec3&);
}



