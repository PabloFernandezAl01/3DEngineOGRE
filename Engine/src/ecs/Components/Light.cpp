#include "Light.h"
#include "Entity.h"
#include "OgreSceneNode.h"
#include "OgreLight.h"
#include "RendererManager.h"
#include "OgreSceneManager.h"

void ECS::Light::Init()
{
	auto rendererManager = Renderer::RendererManager::Instance();

	light = rendererManager->GetOgreSceneManager()->createLight(entity->GetName());
	Ogre::SceneNode* node = rendererManager->CreateNodeFromRoot();
	node->attachObject(light);
	entity->SetSceneNode(node);

	// Configuration
	light->setType(Ogre::Light::LightTypes(lightType));
	light->setDiffuseColour(Ogre::ColourValue{ diffuse.r, diffuse.g, diffuse.b });
	light->setSpecularColour(Ogre::ColourValue{ specular.r, specular.g, specular.b });
	light->setAttenuation(range, constant, linear, quadratic);
}