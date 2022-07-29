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

	OpenGL::MeshData data = OpenGL::Square();

	OpenGL::CreateVertexArrayObject(data.vertices, data.indicies, test.VAO);
	OpenGL::CreateTexture("../Resources/Textures/wall.jpg", test.textureID);
	test.p_Shader = new OpenGL::Shader("../Resources/Shaders/OpenGL/Triangle1.shader");
	test.indicies = data.indicies.size();
	

		
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

	auto [width, height] = renderer.GetViewportSize();

	test.p_Shader->Bind();
	test.p_Shader->SetUniformMatrix4fv("model", glm::mat4(1.0));
	test.p_Shader->SetUniformMatrix4fv("view", glm::translate(m_Camera.GetViewMatrix(), glm::vec3(0.0f, 0.0f, -2.0f)));
	test.p_Shader->SetUniformMatrix4fv("projection", glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.01f, 100.f));

	renderer.Draw(test);

	renderer.GetViewport().Unbind();
}


Engine::~Engine() {
}

