#include "Utils.h"
#include "EngineData/EngineData.h"
#include <iostream>
#include <fstream>
#include "Subsystems/EditorCamera/EditorCamera.h"

void Utils::LoadInitFile() {

	std::vector<YAML::Node> initdocs = YAML::LoadAllFromFile("Config/init.yaml");
	
	YAML::Node currentNode = initdocs[0]["Window"];

	if (currentNode["Width"]) {
		EngineData::g_Data.MainWindowSize.x = currentNode["Width"].as<int>();
		EngineData::g_Data.MainWindowSize.y = currentNode["Height"].as<int>();
	}

	currentNode = initdocs[1]["Viewport"];

	
	if (currentNode["Width"]) {
		EngineData::g_Data.ViewportSize.x = currentNode["Width"].as<int>();
		EngineData::g_Data.ViewportSize.y = currentNode["Height"].as<int>();

	}

	currentNode = initdocs[2]["EditorCamera"];
	
	if (currentNode["Position"]) {
		EngineData::g_Data.EditorCameraPosition = { currentNode["Position"][0].as<float>(), currentNode["Position"][1].as<float>(), currentNode["Position"][2].as<float>() };
	}
	if (currentNode["Forward"]) {
		EngineData::g_Data.EditorCameraForward = { currentNode["Forward"][0].as<float>(), currentNode["Forward"][1].as<float>(), currentNode["Forward"][2].as<float>() };
	}
	if (currentNode["Up"]) {
		EngineData::g_Data.EditorCameraUp = { currentNode["Up"][0].as<float>(), currentNode["Up"][1].as<float>(), currentNode["Up"][2].as<float>() };
	}
	if (currentNode["Pitch"]) {
		EngineData::g_Data.EditorCameraPitch = currentNode["Pitch"].as<float>();
	}
	if (currentNode["Yaw"]) {
		EngineData::g_Data.EditorCameraYaw = currentNode["Yaw"].as<float>();
	}

}

void Utils::SaveInitParams() {

	YAML::Emitter saveParams{};

	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "Window";
	saveParams << YAML::BeginMap; // Values
	saveParams << YAML::Key << "Width" << YAML::Value << EngineData::g_Data.MainWindowSize.x;
	saveParams << YAML::Key << "Height" << YAML::Value << EngineData::g_Data.MainWindowSize.y;
	saveParams << YAML::EndMap;
	saveParams << YAML::EndMap;

	saveParams << YAML::BeginMap; //Viewport
	saveParams << YAML::Key << "Viewport";
	saveParams << YAML::BeginMap; //Values
	saveParams << YAML::Key << "Width" << YAML::Value << EngineData::g_Data.ViewportSize.x;
	saveParams << YAML::Key << "Height" << YAML::Value << EngineData::g_Data.ViewportSize.y;
	saveParams << YAML::EndMap; //Values
	saveParams << YAML::EndMap; //Viewport

	
	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "EditorCamera";
	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "Position" << YAML::Value << YAML::Flow << YAML::BeginSeq << EditorCamera::Position.x << EditorCamera::Position.y << EditorCamera::Position.z << YAML::EndSeq;
	saveParams << YAML::Key << "Forward" << YAML::Value << YAML::Flow << YAML::BeginSeq << EditorCamera::Forward.x << EditorCamera::Forward.y << EditorCamera::Forward.z << YAML::EndSeq;
	saveParams << YAML::Key << "Up" << YAML::Value << YAML::Flow << YAML::BeginSeq << EditorCamera::Up.x << EditorCamera::Up.y << EditorCamera::Up.z << YAML::EndSeq;
	saveParams << YAML::Key << "Pitch" << YAML::Value << EditorCamera::Pitch;
	saveParams << YAML::Key << "Yaw" << YAML::Value << EditorCamera::Yaw;
	saveParams << YAML::EndMap;
	saveParams << YAML::EndMap;
	
	std::ofstream file("Config/init.yaml");

	file << saveParams.c_str(); 

	file.close();

}
