#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace EditorCamera {

	inline glm::vec3 Rotation(0.0f, -90.f, 0.0f);

	void Init(const glm::vec3&, const glm::vec3&, const glm::vec3&, const bool&);
	
	glm::mat4 GetViewMatrix();

	void Rotate();

	void Move(const glm::vec3&);
}



