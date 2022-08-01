#include "InputManager.h"
#include "Engine.h"


void InputManager::RegisterKeyCallback(void(*callback)(GLFWwindow window, int key, int scancode, int action, int mods)) {

	glfwSetKeyCallback(Engine::MainWindow, reinterpret_cast<GLFWkeyfun>(callback));
}
