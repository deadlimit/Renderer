#pragma once

#include "OpenGLCore.h"
#include <string>
#include <map>

namespace OpenGL {
	
	class Shader {
		
	public:
		Shader(const std::string&);
		~Shader();
		
		void Bind();

		Shader(const Shader&);
		Shader(Shader&&) = delete;

		inline const unsigned int GetID() const { return m_ID; }

	public:

		void SetUniform1f(const char*, float);
		void SetUniform1i(const char*, int);
		void SetUniform1ui(const char*, unsigned int);
		void SetUniform2f(const char*, float, float);
		void SetUniform3f(const char*, float, float, float);
		void SetUniform4f(const char*, float, float, float, float);
		

	private:
	
		std::map<std::string, int> m_Uniforms;

		std::tuple<const char*, const char*> ExtractSourceCode(const std::string&);

		bool CreateShader(GLuint&, GLuint, const char*);

		bool CheckStatus(GLuint&, GLuint);

		void GetUniformLocations();

		unsigned int m_ID;

	};
}


