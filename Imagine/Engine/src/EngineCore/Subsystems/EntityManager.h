#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include "Renderer/Renderer.h"

namespace EntityManager {

	//Bad name, rename plz
	using RenderData = std::unordered_map<uint32_t, Renderer::RenderInformation>;

	struct Entity {
		uint32_t ID;
		std::string Name;
		std::string Texture;
		std::string Shader;
	};


	inline RenderData RenderingData;
	inline std::vector<Entity> Entities;
	
	void CreateEntity(const std::vector<Vertex>&, const std::vector<uint32_t>&, const std::string&, const std::string&, const std::string&, glm::vec3 defaultPosition);
	void SerializeEntities(std::fstream&);

}
