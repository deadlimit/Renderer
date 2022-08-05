#include "Utils.h"
#include "EngineData/EngineData.h"
#include <iostream>
#include <fstream>

void Utils::LoadInitFile() {
	
	YAML::Node init = YAML::LoadFile("Config/init.yaml");

	YAML::Node windowSize = init["Window"];

	if (windowSize["width"]) {
		EngineData::g_Data.MainWindowSize.x = windowSize["width"].as<int>();
		EngineData::g_Data.MainWindowSize.y = windowSize["height"].as<int>();
	}

	YAML::Node viewportSize = init["Viewport"];

	if (viewportSize["width"]) {
	
		EngineData::g_Data.ViewportSize.x = viewportSize["width"].as<int>();
		EngineData::g_Data.ViewportSize.y = viewportSize["height"].as<int>();

	}

}

void Utils::SaveInitParams() {

	YAML::Emitter saveParams;
	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "Window";
	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "width" << YAML::Value << EngineData::g_Data.MainWindowSize.x;
	saveParams << YAML::Key << "height" << YAML::Value << EngineData::g_Data.MainWindowSize.y;
	saveParams << YAML::EndMap;
	saveParams << YAML::EndMap;

	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "Viewport";
	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "width" << YAML::Value << EngineData::g_Data.ViewportSize.x;
	saveParams << YAML::Key << "height" << YAML::Value << EngineData::g_Data.ViewportSize.y;
	saveParams << YAML::EndMap;
	saveParams << YAML::EndMap;

	std::ofstream file("Config/init.yaml");

	file << saveParams.c_str(); 

	file.close();

}
