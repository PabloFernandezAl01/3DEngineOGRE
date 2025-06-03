#include "RendererManager.h"
#include "OgreRoot.h"

namespace Renderer {

	RendererManager::RendererManager(const ConfigData& data) 
	{
		windowTitle = data.windowTitle;

		InitOgre();

		valid = true;
	}

	void RendererManager::InitOgre()
	{
		ctx.initApp();

		root = ctx.getRoot();
		sceneManager = root->createSceneManager();
	}

	void RendererManager::CloseOgre()
	{
		ctx.closeApp();
	}

	bool RendererManager::Valid() 
	{
		return valid;
	}

	RendererManager::~RendererManager()
	{
		
	}

	void RendererManager::PresentRenderer()
	{
		root->renderOneFrame();
	}
}