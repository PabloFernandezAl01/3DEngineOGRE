#include "RendererManager.h"
#include "OgreRenderWindow.h"
#include "OgreConfigFile.h"
#include <OgreWindowEventUtilities.h>
#include <SDL.h>
#include <Log.h>
#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>
#include <OgreMeshManager.h>
#include <OgreGpuProgramManager.h>

namespace Renderer {
	
	RendererManager::RendererManager(const ConfigData& data)
	{
		valid = InitOgre(data);
	}

	bool RendererManager::InitOgre(const ConfigData& data)
	{
		root = new Ogre::Root();

		auto renderers = root->getAvailableRenderers();
		root->setRenderSystem(renderers[0]);

		root->initialise(false);

		LoadResources();

		if (!CreateSDLWindow(data))
		{
			delete root;
			return false;
		}

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		sceneManager = root->createSceneManager();

		if (!sceneManager)
		{
			delete root;
			return false;
		}

		return true;
	}

	void RendererManager::CloseOgre()
	{
		Ogre::ResourceGroupManager::getSingleton().clearResourceGroup("General");
		Ogre::MaterialManager::getSingleton().removeAll();
		Ogre::TextureManager::getSingleton().removeAll();
		Ogre::MeshManager::getSingleton().removeAll();
		Ogre::GpuProgramManager::getSingleton().removeAll();
		Ogre::HighLevelGpuProgramManager::getSingleton().removeAll();

		delete root;
	}

	bool RendererManager::CreateSDLWindow(const ConfigData& data)
	{
		// Initialize SDL
		int sdlInit_ret = SDL_Init(SDL_INIT_VIDEO);

		if (sdlInit_ret < 0)
		{
			Log::PrintError("SDL Initialization", SDL_GetError());
			return false;
		}

		renderWindow = root->createRenderWindow(data.windowTitle, data.windowSize.GetX(), data.windowSize.GetY(), data.fullscreen);
		renderWindow->setVSyncEnabled(data.vsync);
		size_t hwnd = 0;
		renderWindow->getCustomAttribute("WINDOW", &hwnd);
		sdlWindow = SDL_CreateWindowFrom((void*)hwnd);

		if (!sdlWindow)
		{
			SDL_Quit();

			Log::PrintError("SDL Create Window From", SDL_GetError());
			return false;
		}

		winWidth = data.windowSize.GetX();
		winHeight = data.windowSize.GetY();

		return true;
	}

	void RendererManager::LoadResources()
	{
		Ogre::ConfigFile cf;
		cf.load("resources.cfg");

		auto settingsBySection = cf.getSettingsBySection(); // Devuelve std::map

		for (const auto& [sectionName, settings] : settingsBySection)
		{
			for (const auto& [type, path] : settings)
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(path, type, sectionName);
			}
		}
	}

	bool RendererManager::Valid() 
	{
		return valid;
	}

	RendererManager::~RendererManager()
	{
		CloseOgre();
		SDL_Quit();
	}

	Ogre::SceneNode* RendererManager::CreateNodeFromRoot()
	{
		return sceneManager->getRootSceneNode()->createChildSceneNode();
	}

	Ogre::Viewport* RendererManager::CreateViewport(Ogre::Camera* cam)
	{
		return renderWindow->addViewport(cam);
	}

	void RendererManager::SetAmbientLight(CRefColor color)
	{
		sceneManager->setAmbientLight(Ogre::ColourValue{ color.r, color.g, color.b });
	}

	void RendererManager::SetShadowTechnique()
	{

	}

	void RendererManager::SetFog()
	{

	}

	void RendererManager::SetDisplaySceneNodes(bool display)
	{
		sceneManager->setDisplaySceneNodes(display);
	}

	void RendererManager::SetSkyBox(bool active, CRefString name)
	{
		sceneManager->setSkyBox(active, name);
	}

	void RendererManager::SetFullscreen(bool fullscreen)
	{
		auto flags = SDL_GetWindowFlags(sdlWindow);

		if (flags & SDL_WINDOW_FULLSCREEN)
		{
			if (SDL_SetWindowFullscreen(sdlWindow, 0) < 0)
				Log::PrintError("Window FullScreen Error", SDL_GetError());
		}
		else
			if (SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
				Log::PrintError("Window FullScreen Error", SDL_GetError());
	}

	void RendererManager::PresentRenderer()
	{
		root->renderOneFrame();
	}
}