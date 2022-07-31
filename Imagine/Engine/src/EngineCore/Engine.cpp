#include "Engine.h"
#include "Subsystems//GUI/GUI.h"
#include "Subsystems/ResourceManager/ResourceManager.h"
#include <yaml-cpp/yaml.h>
#include "Subsystems/EntityManager.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "../Utils.h"

void Engine::Init() {
	
	glfwInit();

	Utils::LoadInitFile();

	m_Window = glfwCreateWindow(Utils::g_InitParams.windowWidth, Utils::g_InitParams.windowHeight, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to init GLAD");
		return;
	}

	/*
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Window" << YAML::Value << YAML::BeginMap; 
	out << YAML::Key << "width" << YAML::Value << 1280;
	out << YAML::Key << "height" << YAML::Value << 720;
	out << YAML::EndMap;
	out << YAML::EndMap;

	std::ofstream outstream("Config/init.yaml");

	outstream << out.c_str();
	
	outstream.close();
	*/
	

	
	Renderer::Init(m_Window, Utils::g_InitParams.viewportHeight, Utils::g_InitParams.viewportHeight);
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

	Utils::SaveInitParams();

	GUI::Shutdown();
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

