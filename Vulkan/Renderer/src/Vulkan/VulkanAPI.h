#pragma once

#include "../GraphicsAPI.h"
#include "VulkanCore.h"
#include "GPU.h"
#include "Mesh.h"
#include "MeshFactory.h"


class VulkanInstance;

class VulkanAPI : public GraphicsAPI {

public:

	VulkanAPI() = default;
	virtual void Init() override;
	virtual void Run() override;
	virtual void Clean() override;
	
private:

	void Draw(const Mesh&);
	
	void InitSyncObjects();

	void UpdateSwapchain() const;

	void CompileShaders();


private:

	static void OnWindowResize(GLFWwindow*, int, int);

	bool m_WindowWasResized;

	const int m_AvailableFrames = 2;
	uint32_t m_CurrentFrame;
	GLFWwindow* m_Window;

	VulkanInstance* m_Instance;

	MeshFactory* m_MeshFactory;

	std::vector<VkSemaphore> m_ImageAvailableSemaphore;
	std::vector<VkSemaphore> m_RenderFinishedSemaphore;
	std::vector<VkFence> m_InFlightFence;

	std::vector<Mesh> m_Meshes;

	VkPhysicalDevice m_GPU;
	VkDevice m_Device;


};
