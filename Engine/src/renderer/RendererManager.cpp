#include "RendererManager.h"
#include "OgreRenderWindow.h"

namespace Renderer {
	
	RendererManager::RendererManager(const ConfigData& data)
	{
		valid = InitOgre(data);
	}

	bool RendererManager::InitOgre(const ConfigData& data)
	{
		root = new Ogre::Root();

		root->loadPlugin("RenderSystem_GL");
		// o si usas Direct3D:
		// root->loadPlugin("RenderSystem_Direct3D11");

		// Luego seleccionar uno de los sistemas:
		auto renderers = root->getAvailableRenderers();
		root->setRenderSystem(renderers[0]); // o el que desees


		root->initialise(false);

		renderWindow = root->createRenderWindow(data.windowTitle, data.windowSize.GetX(), data.windowSize.GetY(), data.fullscreen);
		renderWindow->setVSyncEnabled(data.vsync);

		screenWidth = data.windowSize.GetX();
		screenHeight = data.windowSize.GetY();

		if (!renderWindow)
		{
			delete root;
			return false;
		}

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
	}

	bool RendererManager::Valid() 
	{
		return valid;
	}

	RendererManager::~RendererManager()
	{
		delete root;
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
		renderWindow->setFullscreen(fullscreen, screenWidth, screenHeight);
	}

	void RendererManager::SetVSync(bool active)
	{
		renderWindow->setVSyncEnabled(active);
	}

	void RendererManager::PresentRenderer()
	{
		root->renderOneFrame();
	}
}