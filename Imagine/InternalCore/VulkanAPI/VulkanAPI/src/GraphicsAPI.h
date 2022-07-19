#pragma once

class GraphicsAPI {

public:
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void Clean() = 0;
};

