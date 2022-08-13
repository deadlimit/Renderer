#pragma once
#include "Utils/Math.h"
#include "glm.hpp"
#include "EngineData/EngineData.h"

enum class ViewMode {
	Mode_2D = 0,
	Mode_3D = 1
};


namespace EditorCamera {
	
	inline EngineData::EditorCameraData Params;

	void Init(const EngineData::EditorCameraData&);
	
	glm::mat4 GetViewMatrix();

	void Rotate();

	void Move(const glm::vec3&);
}



