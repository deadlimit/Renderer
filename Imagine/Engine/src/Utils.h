#pragma once
#include "yaml-cpp/yaml.h"
#include <chrono>
#include <glm.hpp>

namespace Utils {

	struct InitParams {
		int windowWidth;
		int windowHeight;
		int viewportWidth;
		int viewportHeight;
		glm::vec2 viewportMinPosition;
		glm::vec2 viewportMaxPosition;
	};

	inline InitParams g_InitParams;

	void LoadInitFile();
	void SaveInitParams();

}
