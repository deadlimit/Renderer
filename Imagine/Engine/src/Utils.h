#pragma once
#include "yaml-cpp/yaml.h"
#include <chrono>

namespace Utils {

	struct InitParams {
		int windowWidth;
		int windowHeight;
		int viewportWidth;
		int viewportHeight;
	};

	inline InitParams g_InitParams;

	void LoadInitFile();
	void SaveInitParams();

}
