#pragma once

#include <Singleton.h>
#include <ETypes.h>
#include <unordered_map>

namespace Resources {

	template<typename T>
	using resources_map = std::unordered_map<std::string, T>;

	class ResourcesManager : public Core::Singleton<ResourcesManager> {

		friend Singleton<ResourcesManager>;

	public:

		~ResourcesManager();

		//Renderer::Texture* AddTexture(CRefString key);

		inline CRefString GetResourcesPath() { return resourcesPath; }
		inline void SetResourcesPath(CRefString path) { resourcesPath = path; }

	private:

		std::string resourcesPath;

		ResourcesManager() {}
		ResourcesManager(CRefString path);
		
		//resources_map<Renderer::Texture*> textures;
		
	};
}

