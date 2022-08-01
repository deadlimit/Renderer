#include "Serializer.h"
#include <vector>
#include "Subsystems/EntityManager.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>

using namespace YAML;

namespace Serializer {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& vector) {

		out << Flow;
		out << BeginSeq << vector.x << vector.y << vector.z << EndSeq;

		return out;
	}

	void SerializeScene(const std::string& savefile) {

		YAML::Emitter out;

		out << BeginMap; //Scene
		out << Key << "Scene" << Value << "Untitled";
		out << Key << "Objects" << Value << BeginSeq;

		for (int i = 0; i < EntityManager::Entities.size(); ++i) {
			out << BeginMap;

			out << Key << "ID" << Value << EntityManager::Entities[i].ID;
			out << Key << "Name" << Value << EntityManager::Entities[i].Name;
			out << Key << "Shader" << Value << EntityManager::Entities[i].Shader;
			out << Key << "Texture" << Value << EntityManager::Entities[i].Texture;
			out << Key << "Position" << Value << EntityManager::RenderingData[EntityManager::Entities[i].ID].transform[3];
			out << EndMap;
		}

		out << EndMap;
		std::ofstream outstream("../Resources/Scenes/" + savefile);

		outstream << out.c_str();

		outstream.close();
	}

	void DeserializeScene(const std::string& savefile) {

		YAML::Node scene = YAML::LoadFile("../Resources/Scenes/" + savefile);

		if (scene["Scene"]) {

			int entityAmount = scene["Objects"].size();

			YAML::Node node;
			
			for (int i = 0; i < entityAmount; ++i) {
				
				node = scene["Objects"][i];
					
				const std::string& name = node["Name"].as<std::string>();
				const std::string& shader = node["Shader"].as<std::string>();
				const std::string& texture = node["Texture"].as<std::string>();
				glm::vec3 position = glm::vec3(node["Position"][0].as<float>(), node["Position"][1].as<float>(), node["Position"][2].as<float>());

				EntityManager::CreateEntity(Renderer::Square().vertices, Renderer::Square().indicies, shader, texture, name, position);

			}

		}
	}

}

