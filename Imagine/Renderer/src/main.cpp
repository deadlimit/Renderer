#include <iostream>
#include "Renderer.h"

int main() {

	Renderer renderer;

	renderer.Init();
	renderer.Run();
	renderer.Clean();

	return 0;
}