#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "gtc/type_ptr.hpp"


namespace OpenGL {

	int Shader::moved = 0;

	Shader::Shader(const std::string& file) {
	

		auto[vertexCode, fragmentCode] = ExtractSourceCode(file);

		GLuint m_VertexShaderID;
		GLuint m_FragmentShaderID;

		std::cout << "Compiling shader" << file << std::endl;

		bool vertexCreateSuccess = CreateShader(m_VertexShaderID, GL_VERTEX_SHADER, vertexCode.c_str());
		bool fragmentCreateSuccess = CreateShader(m_FragmentShaderID, GL_FRAGMENT_SHADER, fragmentCode.c_str());

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

		GetUniformLocations();

		Bind();
	}

	void Shader::Bind() const {

		glUseProgram(m_ID);

	}

	Shader::Shader(const Shader& other) : m_Uniforms(other.m_Uniforms), m_ID(other.m_ID) {
		std::cout << "Copy constructor for Shader" << std::endl;
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


	std::tuple<std::string, std::string> Shader::ExtractSourceCode(const std::string& file) {

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
				extractedCode[shaderTypeID] << line + "\n";
						
				if (line.find("uniform") != line.npos) {
					
					std::string uniform = line.substr(line.find_last_of(' ') + 1);
					uniform.pop_back();

					m_Uniforms[uniform] = -1;
				}
			}
		}

		fileStream.close();

		return { extractedCode[0].str(), extractedCode[1].str()};
	}

	void Shader::GetUniformLocations() {

		for (auto& pair : m_Uniforms) {

			int location = glGetUniformLocation(m_ID, pair.first.c_str());

			m_Uniforms[pair.first] = location;

			if (location == -1) {
				std::cout << pair.first << " is unused" << std::endl;
			}
		}		
	}



	Shader::~Shader() {
		glDeleteProgram(m_ID);
	}

	Shader::Shader(Shader&& other ) : m_Uniforms(std::move(other.m_Uniforms)), m_ID(other.m_ID) {
		other.m_ID = -1;
		other.m_Uniforms.clear();
		std::cout << "Move constructor for Shader" << std::endl;
		moved++;
	}

	void Shader::SetUniform1f(const char* uniform, float value) {
		glUniform1f(m_Uniforms[uniform], value);
	}

	void Shader::SetUniform1i(const char* uniform, int value) {
		glUniform1i(m_Uniforms[uniform], value);
	}

	void Shader::SetUniform1ui(const char* uniform, unsigned int value)  {
		glUniform1ui(m_Uniforms[uniform], value);
	}

	void Shader::SetUniform2f(const char* uniform, float v0, float v1) {
		glUniform2f(m_Uniforms[uniform], v0, v1);
	}

	void Shader::SetUniform3f(const char* uniform, float v0, float v1, float v2) {
		glUniform3f(m_Uniforms[uniform], v0, v1, v2);
	}

	void Shader::SetUniform4f(const char* uniform, float v0, float v1, float v2, float v3) {
		glUniform4f(m_Uniforms[uniform], v0, v1, v2, v3);
	}

	void Shader::SetUniformMatrix4fv(const char* uniform, glm::mat4 value) {
		glUniformMatrix4fv(m_Uniforms[uniform], 1, GL_FALSE, glm::value_ptr(value));
	}

}


