#include "Serializer.h"
#include <vector>
#include "Subsystems/EntityManager.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

using namespace YAML;

void Serializer::SerializeScene(const std::string& savefile) {

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

		out << Key << "Position" << BeginSeq;
		out << EntityManager::Entities[i].Transform[3][0];
		out << EntityManager::Entities[i].Transform[3][1];
		out << EntityManager::Entities[i].Transform[3][2];
		out << EndSeq;

		out << EndMap;
	}

	out << EndMap;
	std::ofstream outstream("../Resources/Scenes/" + savefile);

	outstream << out.c_str();

	outstream.close();
}
