#pragma once

#include "Component.h"

#include <ETypes.h>
#include <list>

namespace Ogre 
{
	class SceneNode;
}

namespace ECS {

	class Transform : public Component {
	public:

		enum class TransformSpace { LOCAL, PARENT, WORLD };

		Transform() {};
		Transform(CRefVector3D position, CRefVector3D scale, CRefQuaternion quaternion);

		void Init() override;

		void Update(float dt) override;

		// World position
		inline CRefVector3D GetPosition() { return position; }
		inline void SetPosition(CRefVector3D position) { this->position = position; }

		// World rotation
		inline CRefQuaternion GetOrientation() { return orientation; }
		inline void SetOrientation(CRefQuaternion rotation) { this->orientation = rotation; }

		// World scale
		inline CRefVector3D GetScale() { return scale; }
		inline void SetScale(CRefVector3D scale) { this->scale = scale; }

		// Modifiers
		inline void Translate(CRefVector3D distance) { this->position += distance; }
		inline void Rotate(CRefVector3D eulerAngles) { this->orientation.Rotate(eulerAngles); }
		inline void Scale(CRefVector3D scale) { this->scale += scale; }

		// In degrees
		void Yaw(float degrees, const TransformSpace& ts);
		void Pitch(float degrees, const TransformSpace& ts);
		void Roll(float degrees, const TransformSpace& ts);

		void LookAt(CRefVector3D direction);

	private:

		Core::Vector3D position;
		Core::Vector3D scale{ 1, 1, 1 };
		Core::Quaternion orientation{};

		Ogre::SceneNode* entityNode{};
	};

}