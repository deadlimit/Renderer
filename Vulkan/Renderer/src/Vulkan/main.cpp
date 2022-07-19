#include <iostream>
#include "../Renderer.h"

int main() {

	Renderer renderer(API::VULKAN);

	renderer.Init();
	renderer.Run();
	renderer.Clean();

	return 0;
}