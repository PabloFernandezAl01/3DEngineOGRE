#pragma once

#include "ESingleton.h"
#include "ConfigManager.h"
#include <string>
#include <vector>

class Engine;

namespace Sound {

	class SoundManager : public Core::ESingleton<SoundManager> {

		friend ESingleton<SoundManager>;
		friend Engine;

	public:

		~SoundManager();

	private:

		SoundManager() {};
		SoundManager(const ConfigData& data);

		bool Valid() override;

		bool valid{};
	};
}