#include "Engine.h"
#include "Subsystems//GUI/GUI.h"
#include "Subsystems/ResourceManager/ResourceManager.h"
#include "Subsystems/EntityManager.h"
#include <stdexcept>
#include <iostream>




void Engine::Init() {

	glfwInit();

	m_Window = glfwCreateWindow(1280, 860, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to init GLAD");
		return;
	}

	Renderer::Init(m_Window, 1280, 860);
	GUI::Init(m_Window);
	Renderer::MeshData meshData = Renderer::Square();

	CreateEntity(meshData.vertices, meshData.indicies, "Triangle1.shader", "wall.jpg", "Square 1", glm::vec3(-1.5f, 0.0f, 0.0f));
	CreateEntity(meshData.vertices, meshData.indicies, "Triangle1.shader", "wall.jpg", "Square 2", glm::vec3(1.5f, 0.0f, 0.0f));

}



void Engine::Run() {

	while (!glfwWindowShouldClose(m_Window)) {

		Renderer::Clear(Renderer::Framebuffer.ID);

		glfwPollEvents();

		for (RenderData::iterator& it = m_RenderData.begin(); it != m_RenderData.end(); ++it) {

			it->second.transform = glm::rotate(it->second.transform, glm::radians(0.05f), glm::vec3(1.0f, 1.0f, 1.0f));

			Renderer::BindShader(it->second.shader.ProgramID);
			Renderer::SetUniformMatrix4fv(it->second.shader, "model", it->second.transform);
			Renderer::SetUniformMatrix4fv(it->second.shader, "view", glm::translate(m_Camera.GetViewMatrix(), glm::vec3(0.0f, 0.0f, -5.0f)));
			Renderer::SetUniformMatrix4fv(it->second.shader, "projection", glm::perspective(glm::radians(45.0f), (float)3 / (float)2, 0.01f, 100.f));
		}

		Renderer::Draw(m_RenderData, Renderer::Framebuffer.ID);

		GUI::Draw();

		Renderer::SwapBuffers(*m_Window);
	}
}

int EntityID = 0;

void Engine::CreateEntity(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indicies, const std::string& shader, const std::string& texture, const std::string& name, glm::vec3 defaultPosition) {
	
	Renderer::RenderInformation renderInfo = {};
	renderInfo.transform = glm::translate(glm::mat4(1.0f), defaultPosition);
	Renderer::CreateVertexArrayObject(vertices, indicies, renderInfo.VAO);
	Renderer::CreateTexture("wall.jpg", renderInfo.textureID);
	Renderer::CreateShaderProgram("Triangle1.shader", renderInfo.shader);

	renderInfo.indicies = indicies.size();

	//Mock generate ID
	uint32_t ID = EntityID++;

	m_RenderData.insert({ ID, std::move(renderInfo) });

	EntityManager::Entities.push_back({ ID, name });
}

void Engine::Clean() {
	GUI::Shutdown();
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

