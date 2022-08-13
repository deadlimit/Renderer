#include "Utils.h"
#include "EngineData/EngineData.h"
#include <iostream>
#include <fstream>
#include "Subsystems/EditorCamera/EditorCamera.h"

void Utils::LoadInitFile() {

	std::vector<YAML::Node> initdocs = YAML::LoadAllFromFile("../Config/init.yaml");
	
	YAML::Node currentNode = initdocs[0]["Window"];

	if (currentNode["Width"]) {
		EngineData::g_MainWindow.Size.x = currentNode["Width"].as<float>();
		EngineData::g_MainWindow.Size.y = currentNode["Height"].as<float>();
	}

	currentNode = initdocs[1]["Viewport"];

	if (currentNode["Width"]) {
		EngineData::g_ViewportData.Size.x = currentNode["Width"].as<float>();
		EngineData::g_ViewportData.Size.y = currentNode["Height"].as<float>();

	}

	currentNode = initdocs[2]["EditorCamera"];
	
	if (currentNode["Position"]) {
		EngineData::g_EditorCameraData.Position = { currentNode["Position"][0].as<float>(), currentNode["Position"][1].as<float>(), currentNode["Position"][2].as<float>() };
	}
	if (currentNode["Forward"]) {
		EngineData::g_EditorCameraData.Forward = { currentNode["Forward"][0].as<float>(), currentNode["Forward"][1].as<float>(), currentNode["Forward"][2].as<float>() };
	}
	if (currentNode["Up"]) {
		EngineData::g_EditorCameraData.Up  = { currentNode["Up"][0].as<float>(), currentNode["Up"][1].as<float>(), currentNode["Up"][2].as<float>() };
	}
	if (currentNode["Pitch"]) {
		EngineData::g_EditorCameraData.Pitch = currentNode["Pitch"].as<float>();
	}
	if (currentNode["Yaw"]) {
		EngineData::g_EditorCameraData.Yaw = currentNode["Yaw"].as<float>();
	}
	if (currentNode["Mode"]) {
		const std::string& modeString = currentNode["Mode"].as<std::string>();
		EngineData::g_EditorCameraData.ViewMode = (unsigned int)(modeString == "2D" ? ViewMode::Mode_2D : ViewMode::Mode_3D);
	}

}

void Utils::SaveInitParams() {

	YAML::Emitter saveParams{};

	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "Window";
	saveParams << YAML::BeginMap; // Values
	saveParams << YAML::Key << "Width" << YAML::Value << EngineData::g_MainWindow.Size.x;
	saveParams << YAML::Key << "Height" << YAML::Value << EngineData::g_MainWindow.Size.y;
	saveParams << YAML::EndMap;
	saveParams << YAML::EndMap;

	saveParams << YAML::BeginMap; //Viewport
	saveParams << YAML::Key << "Viewport";
	saveParams << YAML::BeginMap; //Values
	saveParams << YAML::Key << "Width" << YAML::Value << EngineData::g_ViewportData.Size.x;
	saveParams << YAML::Key << "Height" << YAML::Value << EngineData::g_ViewportData.Size.y;
	saveParams << YAML::EndMap; //Values
	saveParams << YAML::EndMap; //Viewport

	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "EditorCamera";
	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "Position" << YAML::Value << YAML::Flow << YAML::BeginSeq << EditorCamera::Params.Position.x << EditorCamera::Params.Position.y << EditorCamera::Params.Position.z << YAML::EndSeq;
	saveParams << YAML::Key << "Forward" << YAML::Value << YAML::Flow << YAML::BeginSeq << EditorCamera::Params.Forward.x << EditorCamera::Params.Forward.y << EditorCamera::Params.Forward.z << YAML::EndSeq;
	saveParams << YAML::Key << "Up" << YAML::Value << YAML::Flow << YAML::BeginSeq << EditorCamera::Params.Up.x << EditorCamera::Params.Up.y << EditorCamera::Params.Up.z << YAML::EndSeq;
	saveParams << YAML::Key << "Pitch" << YAML::Value << EditorCamera::Params.Pitch;
	saveParams << YAML::Key << "Yaw" << YAML::Value << EditorCamera::Params.Yaw;
	saveParams << YAML::Key << "Mode" << YAML::Value << (((int)EditorCamera::Params.ViewMode == 0) ? "2D" : "3D");
	saveParams << YAML::Key << "FOV" << YAML::Value << EditorCamera::Params.FOV;
	saveParams << YAML::EndMap;
	saveParams << YAML::EndMap;
	
	std::ofstream file("../Config/init.yaml");

	file << saveParams.c_str(); 

	file.close();

}
