#pragma once
#include <functional>

namespace InputManager {

	void RegisterKeyCallback(void(*)(struct GLFWwindow, int, int, int, int));

}
