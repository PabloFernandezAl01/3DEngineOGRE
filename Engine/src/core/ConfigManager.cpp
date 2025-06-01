#include "ConfigManager.h"
#include <nlohmann\json.hpp>
#include <fstream>

using namespace nlohmann;

#define JSON_EXTENSION ".json"

#define LoadValue(name, type, notFound) file.contains(name) ? file[name].get<type>() : notFound

namespace Core
{
	ConfigManager::ConfigManager()
	{
		valid = false;
	}

	ConfigManager::ConfigManager(std::string const& path)
	{
		valid = Load(path);
	}

	const ConfigData& ConfigManager::GetData()
	{
		return data;
	}

	bool ConfigManager::Valid()
	{
		return valid;
	}

	bool ConfigManager::Load(std::string const& path) {

		std::ifstream fileStream(path + JSON_EXTENSION);

		if (!fileStream.good())
			return false;

		if (!json::accept(fileStream))
			return false;

		fileStream.clear();
		fileStream.seekg(0);

		json file = json::parse(fileStream);
		fileStream.close();

		// General
		data.game = LoadValue("game", std::string, "Game");
		data.creator = LoadValue("creator", std::string, "");

		// Window
		data.windowTitle = LoadValue("windowTitle", std::string, "Game");
		data.windowIcon = LoadValue("windowIcon", std::string, "assets\\icon.png");
		data.windowSize = LoadValue("windowSize", std::string, "1920, 1080");
		data.vsync = LoadValue("vsync", bool, true);
		data.fullscreen = LoadValue("fullScreen", bool, false);
		data.showCursor = LoadValue("showCursor", bool, true);
		data.bgColor = LoadValue("bgColor", std::string, "0, 0, 0");

		// Physics
		data.gravity = LoadValue("gravity", std::string, "0, -9.81");
		data.debugPhysics = LoadValue("debugPhysics", bool, false);
		data.debugFramerate = LoadValue("debugFrameRate", bool, false);

		data.collisionMatrix = LoadValue("matrix", std::vector<std::vector<bool>>, std::vector<std::vector<bool>>());
		data.layers = LoadValue("layers", std::vector<std::string>, std::vector<std::string>());

		// Input
		data.closeWithEscape = LoadValue("closeWithEscape", bool, true);

		// Keyboard
		data.KB_Jump = LoadValue("KB_Jump", int, 4);
		data.KB_Action = LoadValue("KB_Action", int, 4);

		// Controller
		data.CT_Jump = LoadValue("CT_Jump", int, 0);
		data.CT_Action = LoadValue("CT_Action", int, 2);

		// Overlay
		data.timeToHoldClick = LoadValue("timeToHoldClick", float, 0.1f);
		data.timeToDoubleClick = LoadValue("timeToDoubleClick", float, 0.5f);

		// Audio
		data.frequency = LoadValue("frequency", int, 44100);
		data.channels = LoadValue("channels", int, 2);
		data.chunksize = LoadValue("chunksize", int, 2048);

		// Internal
		data.resourcesPath = LoadValue("path", std::string, "");

		if (data.resourcesPath != "")
			data.resourcesPath += "\\";

		return true;
	}
}


