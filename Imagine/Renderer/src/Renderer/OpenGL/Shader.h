#pragma once

#include "OpenGLCore.h"
#include <string>
#include <map>

namespace OpenGL {
	
	class Shader {
		
	public:
		Shader() {}
		Shader(const std::string&);
		~Shader();
		Shader(Shader&&);
		void Bind() const;

		Shader(const Shader&);

		inline const unsigned int GetID() const { return m_ID; }

	public:

		static int moved;

		void SetUniform1f(const char*, float);
		void SetUniform1i(const char*, int);
		void SetUniform1ui(const char*, unsigned int);
		void SetUniform2f(const char*, float, float);
		void SetUniform3f(const char*, float, float, float);
		void SetUniform4f(const char*, float, float, float, float);
		void SetUniformMatrix4fv(const char*, glm::mat4);

	private:
	
		std::map<std::string, int> m_Uniforms;

		std::tuple<std::string, std::string> ExtractSourceCode(const std::string&);

		bool CreateShader(GLuint&, GLuint, const char*);

		bool CheckStatus(GLuint&, GLuint);

		void GetUniformLocations();

		unsigned int m_ID;

	};



}


