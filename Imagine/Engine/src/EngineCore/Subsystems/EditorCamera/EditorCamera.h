#pragma once
#include "Utils/Math.h"
#include "glm.hpp"

enum class ViewMode {
	Mode_2D = 0,
	Mode_3D = 1
};


namespace EditorCamera {
	
	inline float Pitch;
	inline float Yaw;

	inline glm::vec3 Position;
	inline glm::vec3 Forward;
	inline glm::vec3 Up;

	void Init(const ViewMode);
	
	glm::mat4 GetViewMatrix();

	void Rotate();

	void Move(const glm::vec3&);
}



