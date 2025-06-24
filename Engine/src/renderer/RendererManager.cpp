#include "RendererManager.h"
#include "OgreRenderWindow.h"
#include "OgreConfigFile.h"
#include <OgreWindowEventUtilities.h>
#include <SDL.h>
#include <Log.h>
#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>
#include <OgreMeshManager.h>

namespace Renderer {
	
	RendererManager::RendererManager(const ConfigData& data)
	{
		valid = InitOgre(data);
	}

	bool RendererManager::InitOgre(const ConfigData& data)
	{
		root = new Ogre::Root();

		auto& renderers = root->getAvailableRenderers();
		root->setRenderSystem(renderers[1]);

		root->initialise(false);

		LoadResources();

		if (!CreateSDLWindowFromOgre(data))
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
		delete root;
		root = nullptr;
	}

	bool RendererManager::CreateSDLWindowFromOgre(const ConfigData& data)
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

			Log::PrintError("SDL Create Window From failed", SDL_GetError());
			return false;
		}

		return true;
	}

	void RendererManager::LoadResources()
	{
		Ogre::ConfigFile cf;
		cf.load("resources.cfg");

		auto settingsBySection = cf.getSettingsBySection();

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

	void RendererManager::SetShadowTechnique(const ShadowTechnique& technique)
	{
		sceneManager->setShadowTechnique(Ogre::ShadowTechnique(technique));
	}

	void RendererManager::SetFog(const FogMode& mode, CRefColor color, float expDensity, float linearStart, float linearEnd)
	{
		sceneManager->setFog(Ogre::FogMode(mode), Ogre::ColourValue(color.r, color.g, color.b), expDensity, linearStart, linearEnd);
	}

	void RendererManager::SetDisplaySceneNodes(bool display)
	{
		sceneManager->setDisplaySceneNodes(display);
	}

	void RendererManager::SetSkyBox(bool active, CRefString materialName, float distance, bool drawFirst, CRefQuaternion orientation)
	{
		sceneManager->setSkyBox(active, materialName, distance, drawFirst, Ogre::Quaternion({orientation.GetW(), orientation.GetX(), orientation.GetY(), orientation.GetZ()}));
	}

	void RendererManager::SetSkyDome(bool active, CRefString materialName, float curvature, float tiling, float distance, bool drawFirst, CRefQuaternion orientation)
	{
		sceneManager->setSkyDome(active, materialName, curvature, tiling, distance, drawFirst, Ogre::Quaternion({ orientation.GetW(), orientation.GetX(), orientation.GetY(), orientation.GetZ() }));
	}

	void RendererManager::SetSkyPlane(float distanceToOrigin, CRefVector3D normal, bool active, CRefString materialName, float scale, float tiling, bool drawFirst, float bow, int xSegments, int ySegments)
	{
		Ogre::Plane plane;
		plane.d = distanceToOrigin;
		plane.normal = Ogre::Vector3(normal.GetX(), normal.GetY(), normal.GetZ());

		sceneManager->setSkyPlane(active, plane, materialName, scale, tiling, drawFirst, bow, xSegments, ySegments);
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

	void RendererManager::ShowCursor(bool show)
	{
		if (SDL_ShowCursor(show) < 0)
			Log::PrintError("Show cursor error", SDL_GetError());
	}

	void RendererManager::PresentRenderer()
	{
		root->renderOneFrame();
	}

	void RendererManager::RenameWindow(CRefString name)
	{
		SDL_SetWindowTitle(sdlWindow, name.c_str());
	}

	void RendererManager::SetWindowBordered(bool border)
	{
		SDL_SetWindowBordered(sdlWindow, (SDL_bool)border);
	}

	void RendererManager::ResizeWindow(int w, int h)
	{
		if (w <= 0 || h <= 0)
		{
			Log::PrintError("Invalid size parameters", "The provided height and width must be greater than zero.");
			return;
		}

		SDL_SetWindowSize(sdlWindow, w, h);
	}
}