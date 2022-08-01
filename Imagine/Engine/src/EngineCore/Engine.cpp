#include "Engine.h"
#include "Subsystems//GUI/GUI.h"
#include "Subsystems/ResourceManager/ResourceManager.h"
#include <yaml-cpp/yaml.h>
#include "Subsystems/EntityManager.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "../Utils.h"
#include "Subsystems/Serializer.h"

namespace Engine {

	void Init() {

		glfwInit();

		Utils::LoadInitFile();

		MainWindow = glfwCreateWindow(Utils::g_InitParams.windowWidth, Utils::g_InitParams.windowHeight, "OpenGL", nullptr, nullptr);

		glfwMakeContextCurrent(MainWindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to init GLAD");
			return;
		}

		Renderer::Init(MainWindow, Utils::g_InitParams.viewportHeight, Utils::g_InitParams.viewportHeight);
		GUI::Init(MainWindow);

		Serializer::DeserializeScene("Untitled.yaml");
	}

	void Run() {

		while (!glfwWindowShouldClose(MainWindow)) {

			Renderer::Clear(Renderer::Framebuffer.ID);

			glfwPollEvents();

			for (EntityManager::RenderData::iterator& it = EntityManager::RenderingData.begin(); it != EntityManager::RenderingData.end(); ++it) {

				//it->second.transform = glm::rotate(it->second.transform, glm::radians(0.05f), glm::vec3(0.0f, 0.0f, 1.0f));

				Renderer::BindShader(it->second.shader.ProgramID);
				Renderer::SetUniformMatrix4fv(it->second.shader, "model", it->second.transform);
				Renderer::SetUniformMatrix4fv(it->second.shader, "view", glm::translate(EditorCamera.GetViewMatrix(), glm::vec3(0.0f, 0.0f, -5.0f)));
				Renderer::SetUniformMatrix4fv(it->second.shader, "projection", glm::perspective(glm::radians(45.0f), (float)3 / (float)2, 0.01f, 100.f));
			}

			Renderer::Draw(EntityManager::RenderingData, Renderer::Framebuffer.ID);

			GUI::Draw();

			Renderer::SwapBuffers(*MainWindow);
		}
	}

	void Clean() {

		Utils::SaveInitParams();
		Serializer::SerializeScene("Untitled.yaml");

		/*GUI::Shutdown();
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		*/
	}


}

