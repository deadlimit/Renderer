#include "Engine.h"
#include "Subsystems//GUI/GUI.h"
#include "Subsystems/EditorCamera/EditorCamera.h"
#include "Subsystems/ResourceManager/ResourceManager.h"
#include <yaml-cpp/yaml.h>
#include "Subsystems/EntityManager.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "Utils/Utils.h"
#include "Subsystems/Serializer.h"
#include "Subsystems/InputManager.h"
#include "EngineData/EngineData.h"

namespace Engine {

	void Init() {

		glfwInit();

		Utils::LoadInitFile();
		
		MainWindow = glfwCreateWindow(EngineData::g_Data.MainWindowSize.x, EngineData::g_Data.MainWindowSize.y, "OpenGL", nullptr, nullptr);

		glfwMakeContextCurrent(MainWindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to init GLAD");
			return;
		}

		Renderer::Init(MainWindow, EngineData::g_Data.ViewportSize.x, EngineData::g_Data.ViewportSize.y);
		GUI::Init(MainWindow);

		EditorCamera::Init(EngineData::g_Data.EditorCameraPosition, EngineData::g_Data.EditorCameraForward, EngineData::g_Data.EditorCameraUp, EngineData::g_Data.EditorCameraPitch, EngineData::g_Data.EditorCameraYaw,false);
		
		InputManager::Init();

		Serializer::DeserializeScene("Untitled.yaml");

		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_ESCAPE, { nullptr, [](){glfwSetWindowShouldClose(MainWindow, true); }, nullptr});

	}

	void Run() {

		while (!glfwWindowShouldClose(MainWindow)) {

			Renderer::Clear(Renderer::Framebuffer.ID);

			InputManager::HandleInput();

			for (EntityManager::RenderData::iterator& it = EntityManager::RenderingData.begin(); it != EntityManager::RenderingData.end(); ++it) {

				//it->second.transform = glm::rotate(it->second.transform, glm::radians(0.05f), glm::vec3(0.0f, 0.0f, 1.0f));

				Renderer::BindShader(it->second.shader.ProgramID);
				Renderer::SetUniformMatrix4fv(it->second.shader, "model", it->second.transform);
				Renderer::SetUniformMatrix4fv(it->second.shader, "view", glm::translate(EditorCamera::GetViewMatrix(), glm::vec3(0.0f, 0.0f, -5.0f)));
				Renderer::SetUniformMatrix4fv(it->second.shader, "projection", glm::perspective(glm::radians(45.0f), (float)3 / (float)2, 0.01f, 100.f));
			}

			Renderer::Draw(EntityManager::RenderingData, Renderer::Framebuffer.ID);

			GUI::Draw();
			
			Renderer::SwapBuffers(*MainWindow);
			glfwPollEvents();
		}
	}

	void Clean() {

		Utils::SaveInitParams();
		Serializer::SerializeScene("Untitled.yaml");
	}


}

