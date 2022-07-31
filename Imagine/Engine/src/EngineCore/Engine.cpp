#include "Engine.h"
#include "Subsystems//GUI/GUI.h"
#include "Subsystems/ResourceManager/ResourceManager.h"
#include <yaml-cpp/yaml.h>
#include "Subsystems/EntityManager.h"
#include <stdexcept>
#include <iostream>
#include <fstream>

void Engine::Init() {
	
	glfwInit();

	m_Window = glfwCreateWindow(1280, 860, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to init GLAD");
		return;
	}

	
	YAML::Node init = YAML::LoadFile("Config/init.yaml");

	if (init["Window"] && init.IsSequence()) {
	

		std::cout << "Window" << std::endl;
		int width = init[0].as<int>();
		std::cout << width << std::endl;
	}

	Renderer::Init(m_Window, 1280, 860);
	GUI::Init(m_Window);
	Renderer::MeshData meshData = Renderer::Square();

	EntityManager::CreateEntity(meshData.vertices, meshData.indicies, "Triangle1.shader", "wall.jpg", "Square 1", glm::vec3(-1.5f, 1.0f, 2.0f));
	EntityManager::CreateEntity(meshData.vertices, meshData.indicies, "Triangle1.shader", "wall2.jpg", "Square 2", glm::vec3(1.5f, -1.0f, 0.5f));

}

void Engine::Run() {

	while (!glfwWindowShouldClose(m_Window)) {

		Renderer::Clear(Renderer::Framebuffer.ID);

		glfwPollEvents();

		for (EntityManager::RenderData::iterator& it = EntityManager::RenderingData.begin(); it != EntityManager::RenderingData.end(); ++it) {

			it->second.transform = glm::rotate(it->second.transform, glm::radians(0.05f), glm::vec3(1.0f, 1.0f, 1.0f));

			Renderer::BindShader(it->second.shader.ProgramID);
			Renderer::SetUniformMatrix4fv(it->second.shader, "model", it->second.transform);
			Renderer::SetUniformMatrix4fv(it->second.shader, "view", glm::translate(m_Camera.GetViewMatrix(), glm::vec3(0.0f, 0.0f, -5.0f)));
			Renderer::SetUniformMatrix4fv(it->second.shader, "projection", glm::perspective(glm::radians(45.0f), (float)3 / (float)2, 0.01f, 100.f));
		}

		Renderer::Draw(EntityManager::RenderingData, Renderer::Framebuffer.ID);

		GUI::Draw();

		Renderer::SwapBuffers(*m_Window);
	}
}



void Engine::Clean() {
	GUI::Shutdown();
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

