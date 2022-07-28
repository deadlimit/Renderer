#pragma once

#include "VulkanCore.h"
#include <vector>

namespace Vulkan {

	class VulkanDebugger {

	public:
		VulkanDebugger();
		~VulkanDebugger();

		inline const std::vector<const char*>& GetValidationLayers() const { return validationLayers; }

	private:

		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		bool SupportsValidationLayers();

	};

}

