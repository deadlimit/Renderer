#pragma once

#include <vector>
#include <string>

namespace EntityManager {

	struct Entity {
		uint32_t ID;
		std::string Name;
	};

	inline std::vector<Entity> Entities;
	
}
