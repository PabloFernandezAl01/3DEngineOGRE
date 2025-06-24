#include "ConfigScene.h"
#include "RendererManager.h"

using namespace Renderer;

void ConfigScene::Start()
{
	auto* renderer = RendererManager::Instance();

	renderer->SetAmbientLight({ 0,0,0 });
	renderer->SetDisplaySceneNodes(true);
	renderer->SetShadowTechnique(Renderer::RendererManager::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

	// SKY
	renderer->SetSkyBox(true, "Examples/SpaceSkyBox");
	//renderer->SetSkyDome(true, "Examples/CloudySky", 5, 8);
	//renderer->SetSkyPlane(1000, { 0, -1, 0 }, true, "Examples/SpaceSkyPlane", 1500, 75, true, 1.5, 150, 150);

	// FOG
	//renderer->SetFog(RendererManager::FogMode::FOG_EXP, { 0.9f, 0.9f, 0.9f }, 0.002);
}
