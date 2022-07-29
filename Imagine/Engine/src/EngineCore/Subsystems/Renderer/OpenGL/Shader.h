#pragma once

#include "OpenGLCore.h"
#include <string>
#include <map>

namespace Renderer {

	struct Shader {
		uint32_t ProgramID;
		std::map<std::string, int> Uniforms;
	};

	void CreateShaderProgram(const std::string&, Shader&);

	void BindShader(const uint32_t&);
	void DeleteShader(Shader&, const uint32_t&);
	void SetUniform1f(Shader&, const char*, float);
	void SetUniform1i(Shader&, const char*, int);
	void SetUniform1ui(Shader&, const char*, unsigned int);
	void SetUniform2f(Shader&, const char*, float, float);
	void SetUniform3f(Shader&, const char*, float, float, float);
	void SetUniform4f(Shader&, const char*, float, float, float, float);
	void SetUniformMatrix4fv(Shader&, const char*, glm::mat4);


}

