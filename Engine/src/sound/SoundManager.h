#pragma once

#include "Singleton.h"
#include "ConfigManager.h"
#include <string>
#include <vector>

class Engine;

namespace Sound {

	class SoundManager : public Core::Singleton<SoundManager> {

		friend Singleton<SoundManager>;
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