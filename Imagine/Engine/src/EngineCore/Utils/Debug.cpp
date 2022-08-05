#include "Debug.h"
#include "Subsystems/GUI/GUI.h"

void Debug::Log(const std::string& message) {
	GUI::PrintToConsole(message);
}
