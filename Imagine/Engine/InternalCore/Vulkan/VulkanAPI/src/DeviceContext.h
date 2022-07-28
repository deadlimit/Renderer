#pragma once

#include "GPU.h"
#include "GPUHandle.h"

namespace Vulkan {

	struct DeviceContext {
		GPU* GPU;
		GPUHandle* Handle;
	};

}