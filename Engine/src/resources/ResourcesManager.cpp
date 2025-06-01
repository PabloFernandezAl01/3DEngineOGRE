#include "ResourcesManager.h"

Resources::ResourcesManager::ResourcesManager(CRefString path)
{
	SetResourcesPath(path);
}

Resources::ResourcesManager::~ResourcesManager() {

	/*for (auto & texture : textures) delete texture.second;
	textures.clear();*/
}

//Renderer::Texture* Resources::ResourcesManager::AddTexture(CRefString key) 
//{
//	if (textures.contains(key))
//		return textures.at(key);
//
//	auto* t = new Renderer::Texture(resourcesPath + key);
//
//	textures.insert(std::make_pair(key, t));
//
//	return t;
//}