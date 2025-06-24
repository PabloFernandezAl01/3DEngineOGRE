#include "PlaneMesh.h"
#include "Entity.h"
#include "OgreSceneNode.h"
#include "RendererManager.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreMeshManager.h"

void ECS::PlaneMesh::Init()
{
	auto rendererManager = Renderer::RendererManager::Instance();

	Ogre::Plane plane({ normal.GetX(), normal.GetY(), normal.GetZ() }, { distanceFromOrigin.GetX(), distanceFromOrigin.GetY(), distanceFromOrigin.GetZ() });

	Ogre::MeshManager::getSingleton().createPlane(name, Ogre::RGN_AUTODETECT, plane, size.GetX(), size.GetY(), segments.GetX(), segments.GetY(),
												  true, numTexCoordSets, uTile, vTile, { upVector.GetX(), upVector.GetY(), upVector.GetZ() });

	mesh = rendererManager->GetOgreSceneManager()->createEntity(name);
	Ogre::SceneNode* node = entity->GetSceneNode();
	node->attachObject(mesh);

	// Configuration
	mesh->setCastShadows(castShadows);

	if (!materialName.empty())
		mesh->setMaterialName(materialName);

}
