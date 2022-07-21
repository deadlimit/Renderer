#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace OpenGL {

	Shader::Shader(const std::string& file) {
	
		auto[vertexCode, fragmentCode] = ExtractSourceCode(file);

		GLuint m_VertexShaderID;
		GLuint m_FragmentShaderID;

		std::cout << "Compiling shader" << file << std::endl;

		bool vertexCreateSuccess = CreateShader(m_VertexShaderID, GL_VERTEX_SHADER, vertexCode);
		bool fragmentCreateSuccess = CreateShader(m_FragmentShaderID, GL_FRAGMENT_SHADER, fragmentCode);

		if (!vertexCreateSuccess || !fragmentCreateSuccess)
			throw std::runtime_error("Failed to create shader");

		m_ID = glCreateProgram();
		glAttachShader(m_ID, m_VertexShaderID);
		glAttachShader(m_ID, m_FragmentShaderID);
		glLinkProgram(m_ID);
	
		bool successfulLink = CheckStatus(m_ID, GL_LINK_STATUS);

		if(!successfulLink)
			throw std::runtime_error("Failed to link " + file);

		glDeleteShader(m_VertexShaderID);
		glDeleteShader(m_FragmentShaderID);
	}

	bool Shader::CreateShader(GLuint& shaderID, GLuint type, const char* sourceCode) {
		shaderID = glCreateShader(type);

		glShaderSource(shaderID, 1, &sourceCode, nullptr);

		glCompileShader(shaderID);

		return CheckStatus(shaderID, GL_COMPILE_STATUS);
	}

	bool Shader::CheckStatus(GLuint& ID, GLuint type) {

		int compileSuccess;
		char failLog[512];

		if (type == GL_COMPILE_STATUS)
			glGetShaderiv(ID, type, &compileSuccess);
		else
			glGetProgramiv(ID, type, &compileSuccess);
		
		if (!compileSuccess) {

			switch (type) {

			case GL_COMPILE_STATUS:
				glGetShaderInfoLog(ID, 512, NULL, failLog);
				break;
			case GL_LINK_STATUS:
				glGetProgramInfoLog(ID, 512, NULL, failLog);
				break;
			}

			std::cout << failLog << std::endl;

			return false;
		}

		return true;

	}

	std::tuple<const char*, const char*> Shader::ExtractSourceCode(const std::string& file) {

		std::ifstream fileStream(file);

		if (!fileStream.is_open()) {
			std::cout << "Could not open " << file << std::endl;
			return { "", "" };
		}


		std::stringstream extractedCode[2];

		std::string line;

		unsigned int shaderTypeID = -1;

		while (std::getline(fileStream, line)) {

			if (line.find("#TYPE VERTEX") != line.npos) {
				shaderTypeID = 0;
			}

			else if (line.find("#TYPE FRAGMENT") != line.npos) {
				shaderTypeID = 1;
			}

			else {
				extractedCode[shaderTypeID] << line << "\n";
			}

		}

		fileStream.close();

		return { extractedCode[0].str().c_str(), extractedCode[1].str().c_str()};
	}

	
	void Shader::Bind() {

		glUseProgram(m_ID);

	}

	Shader::~Shader() {
		glDeleteProgram(m_ID);
	}



}


