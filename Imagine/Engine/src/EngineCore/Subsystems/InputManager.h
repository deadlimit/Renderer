#pragma once

#define BUTTON_ACTIVE	0x01
#define BUTTON_INIT		0x02
#define BUTTON_COLD		0x04
#define BUTTON_RELEASED	0x08

enum class InputType {
	KEY = 0,
	MOUSE = 1
};

typedef void(*Action)();

struct InputAction {
	Action start;
	Action run;
	Action end;
	unsigned char status = BUTTON_COLD;
};

namespace InputManager {

	void Init();
	void RegisterCallback(InputType, const int&, const InputAction&);
	void HandleInput();
}
