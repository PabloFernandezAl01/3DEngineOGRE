#pragma once

#include <ConfigManager.h>
#include <ESingleton.h>
#include <ETypes.h>
#include "OgreRoot.h"

class SDL_Window;

namespace Renderer {

	class RendererManager : public Core::ESingleton<RendererManager> {

		friend ESingleton<RendererManager>;

	public:

		enum class FogMode { FOG_NONE, FOG_EXP, FOG_EXP2, FOG_LINEAR };

        enum class ShadowTechnique
        {
            SHADOWTYPE_NONE = 0x00,
            SHADOWDETAILTYPE_ADDITIVE = 0x01,
            SHADOWDETAILTYPE_MODULATIVE = 0x02,
            SHADOWDETAILTYPE_INTEGRATED = 0x04,
            SHADOWDETAILTYPE_STENCIL = 0x10,
            SHADOWDETAILTYPE_TEXTURE = 0x20,
            SHADOWTYPE_STENCIL_MODULATIVE = SHADOWDETAILTYPE_STENCIL | SHADOWDETAILTYPE_MODULATIVE,
            SHADOWTYPE_STENCIL_ADDITIVE = SHADOWDETAILTYPE_STENCIL | SHADOWDETAILTYPE_ADDITIVE,
            SHADOWTYPE_TEXTURE_MODULATIVE = SHADOWDETAILTYPE_TEXTURE | SHADOWDETAILTYPE_MODULATIVE,
            SHADOWTYPE_TEXTURE_ADDITIVE = SHADOWDETAILTYPE_TEXTURE | SHADOWDETAILTYPE_ADDITIVE,
            SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED = SHADOWTYPE_TEXTURE_ADDITIVE | SHADOWDETAILTYPE_INTEGRATED,
            SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED = SHADOWTYPE_TEXTURE_MODULATIVE | SHADOWDETAILTYPE_INTEGRATED
        };

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
		void SetShadowTechnique(const ShadowTechnique& technique);
		void SetFog(const FogMode& mode = FogMode::FOG_NONE, CRefColor color = {0,0,0}, float expDensity = 0.001f, float linearStart = 0.f, float linearEnd = 1.f);
		void SetDisplaySceneNodes(bool display);
		void SetSkyBox(bool active, CRefString materialName, float distance = 5000.f, bool drawFirst = true, CRefQuaternion orientation = Quaternion::Identity());

		/*
		* Curvature: Suggested to use values between 2 and 65
		*/
		void SetSkyDome(bool active, CRefString materialName, float curvature = 10.f, float tiling = 8.f, float distance = 4000.f, bool drawFirst = true, CRefQuaternion orientation = Quaternion::Identity());
		void SetSkyPlane(float distanceToOrigin, CRefVector3D normal, bool active, CRefString materialName, float scale = 1000.f, float tiling = 10.f, bool drawFirst = true, float bow = 0.f,
						 int xSegments = 1, int ySegments = 1);

		// Window
		void SetFullscreen(bool fullscreen);
		void ShowCursor(bool show);
		void RenameWindow(CRefString name);
		void SetWindowBordered(bool bordered);
		void ResizeWindow(int w, int h);

	private:

		RendererManager() {};
		RendererManager(const ConfigData& data);

		bool InitOgre(const ConfigData& data);
		void CloseOgre();

		bool CreateSDLWindowFromOgre(const ConfigData& data);

		void LoadResources();

		bool valid{};

		// SDL
		SDL_Window* sdlWindow{};

		// OGRE
		Ogre::Root* root{};
		Ogre::SceneManager* sceneManager{};
		Ogre::RenderWindow* renderWindow{};
	};
}
