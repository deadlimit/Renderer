#pragma once
#include "Utils/Math.h"
#include "glm.hpp"
namespace EditorCamera {
	
	inline float Pitch;
	inline float Yaw;

	inline glm::vec3 Position;
	inline glm::vec3 Forward;
	inline glm::vec3 Up;

	void Init(const Vector3&, const Vector3&, const Vector3&, const float&, const float&, const bool&);
	
	glm::mat4 GetViewMatrix();

	void Rotate();

	void Move(const glm::vec3&);
}



