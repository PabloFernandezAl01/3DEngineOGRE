#include "Transform.h"
#include "Vector2D.h"
#include "Entity.h"
#include "OgreSceneNode.h"

namespace ECS {

	Transform::Transform(CRefVector3D position, CRefVector3D scale, CRefQuaternion quaternion) : position(position), scale(scale), rotation(rotation) {}

	void Transform::Update(float dt)
	{
		/* Update OGRE node with transform position, rotation and scale */

		// Position
		entity->GetSceneNode()->setPosition({ position.GetX(), position.GetY(), position.GetZ() });

		// Rotation
		entity->GetSceneNode()->setOrientation({ rotation.GetX(), rotation.GetY(), rotation.GetZ(), rotation.GetW() });

		// Scale
		entity->GetSceneNode()->setScale({ scale.GetX(), scale.GetY(), scale.GetZ() });
	}
	void Transform::LookAt(CRefVector3D direction)
	{
		entity->GetSceneNode()->lookAt({ direction.GetX(), direction.GetY(), direction.GetZ() }, Ogre::Node::TransformSpace::TS_WORLD);
	}
}