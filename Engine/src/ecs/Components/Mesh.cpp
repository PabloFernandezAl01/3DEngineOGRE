#include "Mesh.h"
#include "Entity.h"
#include "OgreSceneNode.h"
#include "RendererManager.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"

void ECS::Mesh::Init()
{
	auto rendererManager = Renderer::RendererManager::Instance();

	mesh = rendererManager->GetOgreSceneManager()->createEntity(meshName);
	Ogre::SceneNode* node = entity->GetSceneNode();
	node->attachObject(mesh);

	// Configuration
	if (!materialName.empty())
		mesh->setMaterialName(materialName);
}