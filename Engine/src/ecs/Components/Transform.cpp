#include "Transform.h"
#include "Vector2D.h"
#include "Entity.h"
#include "OgreSceneNode.h"
#include <numbers>

namespace ECS {

	Transform::Transform(CRefVector3D position, CRefVector3D scale, CRefQuaternion orientation) : position(position), scale(scale), orientation(orientation) {}

	void Transform::Init()
	{
		entityNode = entity->GetSceneNode();
	}

	void Transform::Update(float dt)
	{
		/* Update OGRE node with transform position, rotation and scale */

		// Position
		entityNode->setPosition({ position.GetX(), position.GetY(), position.GetZ() });

		// Rotation
		entityNode->setOrientation({ orientation.GetW(), orientation.GetX(), orientation.GetY(), orientation.GetZ() });

		// Scale
		entityNode->setScale({ scale.GetX(), scale.GetY(), scale.GetZ() });
	}

	void Transform::Yaw(float degrees, const TransformSpace& ts)
	{
		entityNode->yaw(Ogre::Radian(degrees * (std::numbers::pi / 180.0f)), Ogre::Node::TransformSpace(ts));
	}

	void Transform::Pitch(float degrees, const TransformSpace& ts)
	{
		entityNode->pitch(Ogre::Radian(degrees * (std::numbers::pi / 180.0f)), Ogre::Node::TransformSpace(ts));
	}

	void Transform::Roll(float degrees, const TransformSpace& ts)
	{
		entityNode->roll(Ogre::Radian(degrees * (std::numbers::pi / 180.0f)), Ogre::Node::TransformSpace(ts));
	}

	void Transform::LookAt(CRefVector3D direction)
	{
		entity->GetSceneNode()->lookAt({ direction.GetX(), direction.GetY(), direction.GetZ() }, Ogre::Node::TransformSpace::TS_WORLD);
	}
}