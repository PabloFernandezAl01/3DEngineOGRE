#pragma once

#include <ConfigManager.h>
#include <ESingleton.h>
#include <ETypes.h>
#include "OgreRoot.h"
#include "OgreApplicationContext.h"

class SDL_Window;

namespace Renderer {

	class RendererManager : public Core::ESingleton<RendererManager> {

		friend ESingleton<RendererManager>;

	public:

		enum class TransformSpace { LOCAL, PARENT, WORLD };

		~RendererManager();

		bool Valid() override;

		void PresentRenderer();

		inline Ogre::SceneManager* GetOgreSceneManager() { return sceneManager; }
		inline Ogre::RenderWindow* GetRenderWindow() { return renderWindow; }
		inline Ogre::Root* GetOgreRoot() { return root; }

		Ogre::SceneNode* CreateNodeFromRoot();
		Ogre::Viewport* CreateViewport(Ogre::Camera* cam);

		// Scene Manager

			void SetAmbientLight(CRefColor color);

			// TODO
			void SetShadowTechnique();

			// TODO
			void SetFog();

			void SetDisplaySceneNodes(bool display);

			void SetSkyBox(bool active, CRefString name);

		// Window

			void SetFullscreen(bool fullscreen);

			inline int GetWindowWidth() const { return winWidth; }
			inline int GetWindowHeight() const { return winHeight; }

	private:

		RendererManager() {};
		RendererManager(const ConfigData& data);

		bool InitOgre(const ConfigData& data);
		void CloseOgre();

		bool CreateSDLWindow(const ConfigData& data);

		void LoadResources();

		bool valid{};

		int winWidth{}, winHeight{};

		// SDL
		SDL_Window* sdlWindow{};

		// OGRE
		OgreBites::ApplicationContext ctx{ "OGREApp" };
		Ogre::Root* root{};
		Ogre::SceneManager* sceneManager{};
		Ogre::RenderWindow* renderWindow{};

	};
}
