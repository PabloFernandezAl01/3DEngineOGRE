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
	Ogre::SceneNode* node = entity->GetSceneNode();
	node->attachObject(light);

	// Configuration
	light->setType(Ogre::Light::LightTypes(lightType));

	switch (lightType)
	{
	case LightType::SPOTLIGHT:
		//light->setSpotlightFalloff(spotLightFallOff);
		light->setSpotlightRange(Ogre::Degree(spotLightInnerAngle), Ogre::Degree(spotLightOuterAngle));
		break;
	}

	light->setDiffuseColour(Ogre::ColourValue{ diffuse.r, diffuse.g, diffuse.b });
	light->setSpecularColour(Ogre::ColourValue{ specular.r, specular.g, specular.b });
	light->setAttenuation(range, constant, linear, quadratic);
	
}