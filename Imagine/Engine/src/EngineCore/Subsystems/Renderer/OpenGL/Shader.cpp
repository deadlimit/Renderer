#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "gtc/type_ptr.hpp"
#include "Subsystems/ResourceManager/ResourceManager.h"
#include "../Debug.h"

namespace Renderer {

	static std::tuple<std::string, std::string> ExtractSourceCode(const std::string& file, std::unordered_map<std::string, int>& uniforms) {


		std::string fullpath = ResourceManager::LoadShader(file);

		std::ifstream fileStream(fullpath);

		if (!fileStream.is_open()) {
			std::cout << "Could not open " << fullpath << std::endl;
			return { "", "" };
		}

		std::stringstream extractedCode[2];

		std::string line;

		unsigned int shaderTypeID = -1;

		while (std::getline(fileStream, line)) {

			if (line.find("#TYPE VERTEX") != line.npos) {
				shaderTypeID = 0;
			} else if (line.find("#TYPE FRAGMENT") != line.npos) {
				shaderTypeID = 1;
			} else {
				extractedCode[shaderTypeID] << line + "\n";

				if (line.find("uniform") != line.npos) {

					std::string uniform = line.substr(line.find_last_of(' ') + 1);
					uniform.pop_back();

					uniforms[uniform] = -1;
				}
			}
		}

		fileStream.close();

		return { extractedCode[0].str(), extractedCode[1].str() };
	}

	static bool CheckStatus(GLuint& ID, GLuint type) {

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

	static bool CreateShader(GLuint& shaderID, GLuint type, const char* sourceCode) {
		shaderID = glCreateShader(type);

		glShaderSource(shaderID, 1, &sourceCode, nullptr);

		glCompileShader(shaderID);

		return CheckStatus(shaderID, GL_COMPILE_STATUS);
	}

	

	static void GetUniformLocations(Shader& shader) {

		for (auto& pair : shader.Uniforms) {

			int location = glGetUniformLocation(shader.ProgramID, pair.first.c_str());

			shader.Uniforms[pair.first] = location;

			if (location == -1) {
				std::cout << pair.first << " is unused" << std::endl;
			}
		}		
	}

	void SetUniform1f(Shader& shader, const char* uniform, float value) {
		glUniform1f(shader.Uniforms[uniform], value);
	}

	void SetUniform1i(Shader& shader, const char* uniform, int value) {
		glUniform1i(shader.Uniforms[uniform], value);
	}

	void SetUniform1ui(Shader& shader, const char* uniform, unsigned int value)  {
		glUniform1ui(shader.Uniforms[uniform], value);
	}

	void SetUniform2f(Shader& shader, const char* uniform, float v0, float v1) {
		glUniform2f(shader.Uniforms[uniform], v0, v1);
	}

	void SetUniform3f(Shader& shader, const char* uniform, float v0, float v1, float v2) {
		glUniform3f(shader.Uniforms[uniform], v0, v1, v2);
	}

	void SetUniform4f(Shader& shader, const char* uniform, float v0, float v1, float v2, float v3) {
		glUniform4f(shader.Uniforms[uniform], v0, v1, v2, v3);
	}

	void SetUniformMatrix4fv(Shader& shader, const char* uniform, glm::mat4 value) {
		glUniformMatrix4fv(shader.Uniforms[uniform], 1, GL_FALSE, glm::value_ptr(value));
	}

	void BindShader(const uint32_t& program) {
		glUseProgram(program);

	}

	void DeleteShader(const uint32_t& program) {
		glDeleteProgram(program);
	}

	void CreateShaderProgram(const std::string& file, Shader& shader) {

		auto [vertexCode, fragmentCode] = ExtractSourceCode(file, shader.Uniforms);

		GLuint m_VertexShaderID;
		GLuint m_FragmentShaderID;

		Debug::Log("Compiling shader " + file);
	
		bool vertexCreateSuccess = CreateShader(m_VertexShaderID, GL_VERTEX_SHADER, vertexCode.c_str());
		bool fragmentCreateSuccess = CreateShader(m_FragmentShaderID, GL_FRAGMENT_SHADER, fragmentCode.c_str());

		if (!vertexCreateSuccess || !fragmentCreateSuccess)
			throw std::runtime_error("Failed to create shader");

		shader.ProgramID = glCreateProgram();
		glAttachShader(shader.ProgramID, m_VertexShaderID);
		glAttachShader(shader.ProgramID, m_FragmentShaderID);
		glLinkProgram(shader.ProgramID);

		bool successfulLink = CheckStatus(shader.ProgramID, GL_LINK_STATUS);

		if (!successfulLink)
			throw std::runtime_error("Failed to link " + file);

		glDeleteShader(m_VertexShaderID);
		glDeleteShader(m_FragmentShaderID);

		GetUniformLocations(shader);
	}

}


