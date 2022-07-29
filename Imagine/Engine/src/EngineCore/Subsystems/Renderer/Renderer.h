#pragma once

#include "OpenGL/OpenGLCore.h"
#include "OpenGL/Camera.h"
#include "OpenGL/Primitives.h"
#include "OpenGL/Texture.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Framebuffer.h"
#include "OpenGL/Primitives.h"
#include "OpenGL/VertexArrayObject.h"
#include <vector>

namespace Renderer {

	struct RenderInformation {
		uint32_t VAO;
		uint32_t textureID;
		uint32_t indicies;
		OpenGL::Shader* p_Shader;
		glm::mat4 transform = glm::mat4(1.0f);
	};

	struct FramebufferInfo {
		uint32_t ID;
		uint32_t ColorAttachment;
	};


	inline FramebufferInfo Framebuffer;

	void Init(GLFWwindow*, uint32_t, uint32_t);
	void Draw(RenderInformation&, const uint32_t = -1);
	void Clear(const uint32_t);
	void ResizeViewport(int, int);
	void SwapBuffers(GLFWwindow&);

	inline float ViewportWidth;
	inline float ViewportHeight;

}

