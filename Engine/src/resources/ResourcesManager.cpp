#include "ResourcesManager.h"
#include <RendererManager.h>
#include <Texture.h>
#include <Font.h>
#include <SoundEffect.h>
#include <Music.h>

Resources::ResourcesManager::ResourcesManager(CRefString path)
{
	SetResourcesPath(path);
}

Resources::ResourcesManager::~ResourcesManager() {

	for (auto & texture : textures) delete texture.second;
	textures.clear();

	for (auto & font : fonts) delete font.second;
	fonts.clear();

	for (auto& sound : sounds) delete sound.second;
	sounds.clear();

	for (auto& it : music) delete it.second;
	music.clear();
}

Renderer::Texture* Resources::ResourcesManager::AddTexture(CRefString key) 
{
	if (textures.contains(key))
		return textures.at(key);

	auto* t = new Renderer::Texture(resourcesPath + key);

	textures.insert(std::make_pair(key, t));

	return t;
}

Renderer::Font* Resources::ResourcesManager::AddFont(CRefString key, int pointSize)
{
	std::string newkey = key + std::to_string(pointSize);

	if (fonts.contains(newkey))
		return fonts.at(newkey);

	auto* t = new Renderer::Font(resourcesPath + key, pointSize);

	fonts.insert(std::make_pair(newkey, t));

	return t;
}

Sound::SoundEffect* Resources::ResourcesManager::AddSound(CRefString key) 
{
	if (sounds.contains(key))
		return sounds.at(key);

	auto* s = new Sound::SoundEffect(resourcesPath + key);

	sounds.insert(std::make_pair(key, s));

	return s;
}

Sound::Music* Resources::ResourcesManager::AddMusic(CRefString key) 
{
	if (music.contains(key))
		return music.at(key);

	auto* m = new Sound::Music(resourcesPath + key);

	music.insert(std::make_pair(key, m));

	return m;
}

