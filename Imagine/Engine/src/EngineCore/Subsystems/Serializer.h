#pragma once
#include <string>

namespace Serializer {
	
	void SerializeScene(const std::string& savefile);

	void DeserializeScene(const std::string& savefile);
	
}
