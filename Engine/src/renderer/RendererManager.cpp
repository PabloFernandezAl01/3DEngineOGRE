#include "RendererManager.h"

namespace Renderer {

	RendererManager::RendererManager(const ConfigData& data) 
	{
		windowTitle = data.windowTitle;

		valid = true;
	}

	bool RendererManager::Valid() 
	{
		return valid;
	}

	RendererManager::~RendererManager()
	{
		
	}

	void RendererManager::ClearRenderer() 
	{

	}

	void RendererManager::PresentRenderer()
	{

	}
}