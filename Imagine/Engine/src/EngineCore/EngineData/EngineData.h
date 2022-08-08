#pragma once
#include "Utils/Math.h"

namespace EngineData {

	struct Data {

		Vector2 MainWindowSize;
		Vector2 ViewportSize;
		Vector4 ViewportWindowPosition;
		//Below should be a struct
		Vector3 EditorCameraPosition;
		float EditorCameraPitch;
		Vector3 EditorCameraForward;
		float EditorCameraYaw;
		Vector3 EditorCameraUp;
	};

	inline Data g_Data;

}


