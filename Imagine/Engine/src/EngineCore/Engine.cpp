#include "Engine.h"
#include <stdexcept>

void Engine::Init() {

	glfwInit();

	m_Window = glfwCreateWindow(1280, 860, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to init GLAD");
		return;
	}

	GUI::Get().Init(m_Window);

	Renderer::Get().Init(m_Window, { 300, 300 });

	//ObjectFactory::CreateGameObject(OpenGL::Square(), SHADER_RESOURCE("Triangle1.shader"), "../Resources/Textures/wall.jpg");
	

	/*go->Bind();
	go->GetMaterial().GetShader().SetUniformMatrix4fv("projection", glm::perspective(glm::radians(45.f), 800.f / 600.0f, 0.01f, 100.f));
	go->GetMaterial().GetShader().SetUniformMatrix4fv("view", glm::translate(m_Camera.GetViewMatrix(), glm::vec3(0.0f, 0.0f, -2.0f)));
	go->GetMaterial().GetShader().SetUniformMatrix4fv("model", go->transform);
	*/


	//m_ActiveGameObjects[go->ID()] = go;

	//m_ActiveMeshes[go->ID()] = go->GetMesh();

}

void Engine::Run() {

	while (!glfwWindowShouldClose(m_Window)) {

		Renderer::Get().Clear();

		glfwPollEvents();
		
		SubitForRendering();

		GUI::Get().Render();

		Renderer::Get().SwapFramebuffer();

	}
}
void Engine::Clean() {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Engine::SubitForRendering() {

	Renderer& renderer = Renderer::Get();

	renderer.GetViewport().MakeRenderTarget();

	/*for (const auto& [ID, mesh] : m_ActiveMeshes) {
		renderer.Draw(*mesh);
	}
	*/
	renderer.GetViewport().Unbind();
}


Engine::~Engine() {
}

