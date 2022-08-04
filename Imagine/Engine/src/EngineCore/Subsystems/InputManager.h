#pragma once
#include <functional>

namespace InputManager {

	void Init();
	void RegisterCallback(const int&, void(*)());
	void HandleInput();
}
