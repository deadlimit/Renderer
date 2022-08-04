#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace EditorCamera {

	void Init(const glm::vec3&, const glm::vec3&, const glm::vec3&, const bool&);

	void Activate();
	
	glm::mat4 GetViewMatrix();

	void Move(const glm::vec3&);
}



