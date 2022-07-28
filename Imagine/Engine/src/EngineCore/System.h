#pragma once

template <typename T>
class System {

public:

	static T& Get() {
		static T instance;
		return instance;
	}

};

