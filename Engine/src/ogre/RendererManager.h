#pragma once

#include <ConfigManager.h>
#include <ESingleton.h>
#include <ETypes.h>
#include "OgreRoot.h"

namespace Ogre
{
}

namespace Renderer {

	class RendererManager : public Core::ESingleton<RendererManager> {

		friend ESingleton<RendererManager>;

	public:

	private:

		//RendererManager(const ConfigData& data);
		

	};
}
