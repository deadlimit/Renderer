#include "EntityManager.h"

namespace EntityManager {

	int EntityID = 0;

	void CreateEntity(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indicies, const std::string& shader, const std::string& texture, const std::string& name, glm::vec3 defaultPosition) {

		Renderer::RenderInformation renderInfo = {};
		renderInfo.transform = glm::translate(glm::mat4(1.0f), defaultPosition);
		Renderer::CreateVertexArrayObject(vertices, indicies, renderInfo.VAO);
		Renderer::CreateTexture("wall.jpg", renderInfo.textureID);
		Renderer::CreateShaderProgram("Triangle1.shader", renderInfo.shader);

		renderInfo.indicies = indicies.size();

		//Mock generate ID
		uint32_t ID = EntityID++;

		RenderingData.insert({ ID, std::move(renderInfo) });

		EntityManager::Entities.push_back({ ID, name });
	}
}

