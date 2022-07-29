#pragma once
#include "OpenGLCore.h"
#include <string>

namespace OpenGL {

	void CreateTexture(const std::string&, uint32_t&);
	void DeleteTexture(const uint32_t&);
}

