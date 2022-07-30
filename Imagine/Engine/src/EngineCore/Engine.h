#pragma once


#include "Subsystems/Renderer/Renderer.h"

#include "glad.h"
#include "glfw3.h"
#include <map>

using RenderData = std::unordered_map<uint32_t, Renderer::RenderInformation>;

class Engine {

public:
	Engine() : m_Camera(glm::mat4(1.0f)) {}
	~Engine();

	void Init();
	void Run();
	void Clean();

private:

	void CreateEntity(const std::vector<Vertex>&, const std::vector<uint32_t>&, const std::string&, const std::string&, glm::vec3 defaultPosition);

	RenderData m_RenderData;	
	GLFWwindow* m_Window;

	Renderer::Camera m_Camera;
};


