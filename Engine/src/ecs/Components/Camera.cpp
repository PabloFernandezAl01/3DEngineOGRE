#include "Camera.h"
#include "Entity.h"
#include "OgreSceneNode.h"
#include "OgreCamera.h"
#include "RendererManager.h"
#include "OgreSceneManager.h"
#include "OgreViewport.h"

void ECS::Camera::Init()
{
	auto rendererManager = Renderer::RendererManager::Instance();

	camera = rendererManager->GetOgreSceneManager()->createCamera(entity->GetName());
	Ogre::SceneNode* node = rendererManager->CreateNodeFromRoot();
	node->attachObject(camera);
	entity->SetSceneNode(node);

	viewport = rendererManager->CreateViewport(camera);

	// Camera configuration
	camera->setFOVy(Ogre::Radian{fovY});
	camera->setNearClipDistance(nearClipDistance);
	camera->setProjectionType(Ogre::ProjectionType(projectionType));
	camera->setAutoAspectRatio(autoAspectRatio);
	camera->setPolygonMode(Ogre::PolygonMode(polygonMode));
	camera->setUseRenderingDistance(useRenderingDistance);
	camera->setRenderingDistance(renderingDistance);

	if (aspectRatio == 0)
	{
		float width = viewport->getActualWidth();
		float height = viewport->getActualHeight();
		camera->setAspectRatio(width / height);
	}
	else
		camera->setAspectRatio(aspectRatio);

	// Viewport configuration
	viewport->setBackgroundColour(Ogre::ColourValue{ backgroundColor.r, backgroundColor.g, backgroundColor.b });
	viewport->setDimensions(viewportX, viewportY, viewportW, viewportH);
	viewport->setOverlaysEnabled(overlaysEnabled);
}