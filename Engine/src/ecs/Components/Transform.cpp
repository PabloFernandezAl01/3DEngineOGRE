#include "Transform.h"
#include "Vector2D.h"
#include "Entity.h"
#include "OgreSceneNode.h"
#include <numbers>
#include <iostream>

namespace ECS {

	Transform::Transform(CRefVector3D position, CRefVector3D scale, CRefQuaternion orientation) : position(position), scale(scale), orientation(orientation) {}

	void Transform::Init()
	{
		entityNode = entity->GetSceneNode();
		
		if (entity->GetParent())
			parentTr = entity->GetParent()->GetComponent<Transform>();
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

	inline Vector3D Transform::GetWorldPosition()
	{
		if (parentTr)
		{
			Vector3D parentWorldPos = parentTr->GetWorldPosition();
			Quaternion parentWorldOri = parentTr->GetWorldOrientation();
			return parentWorldPos + parentWorldOri * position;
		}
		else
		{
			return position;
		}
	}

	inline Quaternion Transform::GetWorldOrientation()
	{
		if (parentTr)
		{
			return parentTr->GetWorldOrientation() * orientation;
		}
		else
		{
			return orientation;
		}
	}

	void Transform::Translate(CRefVector3D distance, const TransformSpace& ts)
	{
		switch (ts)
		{
		case TransformSpace::LOCAL:
			// Move in local axis (affected by the current orientation)
			position += orientation * distance;
			break;
		case TransformSpace::PARENT:
			position += distance;
			break;
		case TransformSpace::WORLD:
			Quaternion parentWorldOri = Quaternion::Identity();

			if (parentTr)
			{
				parentWorldOri = parentTr->GetWorldOrientation();
			}

			position += parentWorldOri.Inverse() * distance;
			break;
		}
	}

	void Transform::Rotate(CRefVector3D eulerAngles, const TransformSpace& ts)
	{
		// Crear cuaternión de rotación desde ángulos de Euler
		Quaternion deltaRotation = Quaternion::FromEulerAngles(eulerAngles);

		switch (ts)
		{
		case TransformSpace::LOCAL:
			orientation = orientation * deltaRotation;
			break;

		case TransformSpace::PARENT:
			orientation = deltaRotation * orientation;
			break;

		case TransformSpace::WORLD:
			if (parentTr)
			{
				Quaternion parentWorldRot = parentTr->GetOrientation();
				Quaternion localDelta = parentWorldRot.Inverse() * deltaRotation * parentWorldRot;
				orientation = localDelta * orientation;
			}
			else
			{
				orientation = deltaRotation * orientation;
			}
			break;
		}
	}

	void Transform::Scale(CRefVector3D deltaScale, const TransformSpace& ts)
	{
		switch (ts)
		{
		case TransformSpace::LOCAL:
			scale += deltaScale;
			break;

		case TransformSpace::PARENT:
			scale += orientation.Inverse() * deltaScale;
			break;

		case TransformSpace::WORLD:
			Quaternion parentWorldOri = Quaternion::Identity();
			if (parentTr)
			{
				parentWorldOri = parentTr->GetWorldOrientation();
			}

			scale += parentWorldOri.Inverse() * deltaScale;
			break;
		}
	}

	void Transform::Yaw(float degrees, const TransformSpace& ts)
	{
		Rotate({ 0, degrees, 0}, ts);
	}

	void Transform::Pitch(float degrees, const TransformSpace& ts)
	{
		Rotate({ degrees, 0, 0 }, ts);
	}

	void Transform::Roll(float degrees, const TransformSpace& ts)
	{
		Rotate({ 0, 0, degrees }, ts);
	}

	Core::Vector3D Transform::Forward()
	{
		return orientation * Vector3D::Forward();
	}

	Core::Vector3D Transform::Right()
	{
		return orientation * Vector3D::Right();
	}

	Core::Vector3D Transform::Up()
	{
		return orientation * Vector3D::Up();
	}
}