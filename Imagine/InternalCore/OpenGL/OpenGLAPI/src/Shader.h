#pragma once

#include "OpenGLCore.h"
#include <string>

namespace OpenGL {
	
	class Shader {
		
	public:
		Shader(const std::string&);
		~Shader();
		
		void Bind();

	private:
	
		static std::tuple<const char*, const char*> ExtractSourceCode(const std::string&);

		bool CreateShader(GLuint&, GLuint, const char*);

		bool CheckStatus(GLuint&, GLuint);

		unsigned int m_ID;

	};
}


