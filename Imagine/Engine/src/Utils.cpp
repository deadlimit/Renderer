#include "Utils.h"
#include <iostream>
#include <fstream>

void Utils::LoadInitFile() {
	
	YAML::Node init = YAML::LoadFile("Config/init.yaml");

	YAML::Node windowSize = init["Window"];

	if (windowSize["width"]) {
		g_InitParams.windowWidth = windowSize["width"].as<int>();
		g_InitParams.windowHeight = windowSize["height"].as<int>();
	}

	
	YAML::Node viewportSize = init["Viewport"];


	if (viewportSize["width"]) {
	
		g_InitParams.viewportWidth = viewportSize["width"].as<int>();
		g_InitParams.viewportHeight = viewportSize["height"].as<int>();

	}

}

void Utils::SaveInitParams() {

	YAML::Emitter saveParams;
	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "Window";
	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "width" << YAML::Value << g_InitParams.windowWidth;
	saveParams << YAML::Key << "height" << YAML::Value << g_InitParams.windowHeight;
	saveParams << YAML::EndMap;
	saveParams << YAML::EndMap;

	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "Viewport";
	saveParams << YAML::BeginMap;
	saveParams << YAML::Key << "width" << YAML::Value << g_InitParams.viewportWidth;
	saveParams << YAML::Key << "height" << YAML::Value << g_InitParams.viewportHeight;
	saveParams << YAML::EndMap;
	saveParams << YAML::EndMap;

	std::ofstream file("Config/init.yaml");

	file << saveParams.c_str(); 

	file.close();

}
