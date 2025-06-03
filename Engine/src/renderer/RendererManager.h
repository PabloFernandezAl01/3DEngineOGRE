#pragma once

#include <ConfigManager.h>
#include <ESingleton.h>

#include "OgreApplicationContext.h"

namespace Ogre
{
	class Root;
	class SceneManager;
	class SceneNode;
}

namespace Renderer {

	class RendererManager : public Core::ESingleton<RendererManager> {

		friend ESingleton<RendererManager>;

	public:

		~RendererManager();

		bool Valid() override;

		void PresentRenderer();

		inline Ogre::SceneManager* GetOgreSceneManager() { return sceneManager; }
		inline Ogre::SceneNode* CreateNodeFromRoot() { return sceneManager->getRootSceneNode()->createChildSceneNode(); }

	private:

		RendererManager() {};
		RendererManager(const ConfigData& data);

		void InitOgre();
		void CloseOgre();

		inline Ogre::Root* GetOgreRoot() { return root; }

		std::string windowTitle{};

		bool valid{};

		// OGRE
		OgreBites::ApplicationContext ctx{"OGREApp"};
		Ogre::Root* root{};
		Ogre::SceneManager* sceneManager{};

	};
}
