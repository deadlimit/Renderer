#include "Engine.h"
#include "Subsystems//GUI/GUI.h"
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


	GUI::Init(m_Window);
	Renderer::Init(m_Window, 1280, 860);

	Renderer::MeshData data = Renderer::Square();

	Renderer::CreateVertexArrayObject(data.vertices, data.indicies, test.VAO);
	Renderer::CreateTexture("../Resources/Textures/wall.jpg", test.textureID);
	Renderer::CreateShaderProgram("../Resources/Shaders/OpenGL/Triangle1.shader", test.shader);
	test.indicies = data.indicies.size();
	
}

void Engine::Run() {

	uint32_t size = sizeof Renderer::RenderInformation;

	GUI::PrintToConsole(std::to_string(size) + " bytes");

	while (!glfwWindowShouldClose(m_Window)) {

		Renderer::Clear(Renderer::Framebuffer.ID);

		glfwPollEvents();

		test.transform = glm::rotate(test.transform, glm::radians(0.05f), glm::vec3(1.0f, 1.0f, 1.0f));
		test.transform = glm::translate(test.transform, glm::vec3(0.0f));
		
		Renderer::BindShader(test.shader.ProgramID);
		Renderer::SetUniformMatrix4fv(test.shader, "model", test.transform);
		Renderer::SetUniformMatrix4fv(test.shader, "view", glm::translate(m_Camera.GetViewMatrix(), glm::vec3(0.0f, 0.0f, -2.0f)));
		Renderer::SetUniformMatrix4fv(test.shader, "projection", glm::perspective(glm::radians(45.0f), (float)3 / (float)2, 0.01f, 100.f));

		Renderer::Draw(test, Renderer::Framebuffer.ID);

		GUI::Draw();

		Renderer::SwapBuffers(*m_Window);

	}
}
void Engine::Clean() { 
	GUI::Shutdown();
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}


Engine::~Engine() {
}

