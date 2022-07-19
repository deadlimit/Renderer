#pragma once

#include "GPU.h"
#include "GPUHandle.h"

struct DeviceContext {
	GPU* GPU;
	GPUHandle* Handle;
};
