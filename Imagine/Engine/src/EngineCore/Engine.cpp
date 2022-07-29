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

	OpenGL::MeshData data = OpenGL::Square();

	OpenGL::CreateVertexArrayObject(data.vertices, data.indicies, test.VAO);
	OpenGL::CreateTexture("../Resources/Textures/wall.jpg", test.textureID);
	test.p_Shader = new OpenGL::Shader("../Resources/Shaders/OpenGL/Triangle1.shader");
	test.indicies = data.indicies.size();
	
}

void Engine::Run() {

	GUI::PrintToConsole("Begin engine run");

	while (!glfwWindowShouldClose(m_Window)) {

		Renderer::Clear(Renderer::Framebuffer.ID);

		glfwPollEvents();

		test.transform = glm::rotate(test.transform, glm::radians(0.05f), glm::vec3(0.0f, 0.0f, 1.0f));
		test.transform = glm::translate(test.transform, glm::vec3(0.0f));
		test.p_Shader->Bind();
		test.p_Shader->SetUniformMatrix4fv("model", test.transform);
		test.p_Shader->SetUniformMatrix4fv("view", glm::translate(m_Camera.GetViewMatrix(), glm::vec3(0.0f, 0.0f, - 2 - glm::sin(glfwGetTime()))));
		test.p_Shader->SetUniformMatrix4fv("projection", glm::perspective(glm::radians(45.0f), (float)3 / (float)2, 0.01f, 100.f));

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

