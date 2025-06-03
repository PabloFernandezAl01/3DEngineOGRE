#pragma once

#include "ETypes.h"
#include "ESingleton.h"
#include <vector>

namespace Core
{
	struct ConfigData {

		// General
		std::string creator{};
		std::string game{};
		bool useSplashScreen{};

		// Window
		std::string windowTitle{};
		std::string windowIcon{};
		Vector2D windowSize{};
		bool vsync{};
		bool fullscreen{};
		bool showCursor{};
		std::string bgColor{};

		// Physics
		bool debugPhysics{};
		bool debugFramerate{};
		Vector2D gravity{};
		std::vector<std::vector<bool>> collisionMatrix{};
		std::vector<std::string> layers{};

		// Input
		bool closeWithEscape{};

		// Keyboard
		int KB_Jump{};
		int KB_Action{};

		// Controller
		int CT_Jump{};
		int CT_Action{};

		// Overlay
		float timeToDoubleClick{};
		float timeToHoldClick{};

		// Audio
		int frequency{};
		int channels{};
		int chunksize{};

		// Internal
		std::string resourcesPath{};

	};

	class ConfigManager : public ESingleton<ConfigManager> {

		friend ESingleton<ConfigManager>;

	public:

		const ConfigData& GetData();

		bool Valid() override;

	private:

		ConfigManager();
		ConfigManager(std::string const& path);

		bool Load(std::string const& path);

		ConfigData data;

		bool valid;

	};
}

