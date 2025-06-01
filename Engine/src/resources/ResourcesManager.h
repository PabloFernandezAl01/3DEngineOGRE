#pragma once

#include <Singleton.h>
#include <ETypes.h>
#include <unordered_map>

namespace Renderer {
	class Texture;
	class Font;
}

namespace Sound {
	class SoundEffect;
	class Music;
}

namespace Resources {

	template<typename T>
	using resources_map = std::unordered_map<std::string, T>;

	class ResourcesManager : public Utilities::Singleton<ResourcesManager> {

		friend Singleton<ResourcesManager>;

	public:

		~ResourcesManager();

		Renderer::Texture* AddTexture(CRefString key);
		Renderer::Font* AddFont(CRefString key, int pointSize);
		Sound::SoundEffect* AddSound(CRefString key);
		Sound::Music* AddMusic(CRefString key);

		inline CRefString GetResourcesPath() { return resourcesPath; }
		inline void SetResourcesPath(CRefString path) { resourcesPath = path; }

	private:

		std::string resourcesPath;

		ResourcesManager() {}
		ResourcesManager(CRefString path);
		
		resources_map<Renderer::Texture*> textures;
		resources_map<Renderer::Font*> fonts;
		resources_map<Sound::SoundEffect*> sounds;
		resources_map<Sound::Music*> music;
	};
}

