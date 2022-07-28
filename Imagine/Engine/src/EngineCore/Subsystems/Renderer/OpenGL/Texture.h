#pragma once
#include "OpenGLCore.h"
#include <string>

namespace OpenGL {

	static uint32_t CreateTexture(const std::string&);
	static void DeleteTexture(uint32_t);
}

