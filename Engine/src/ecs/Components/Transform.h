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
		inline Vector3D GetWorldPosition();

		// World rotation
		inline CRefQuaternion GetOrientation() { return orientation; }
		inline void SetOrientation(CRefQuaternion rotation) { this->orientation = rotation; }
		inline Quaternion GetWorldOrientation();

		// World scale
		inline CRefVector3D GetScale() { return scale; }
		inline void SetScale(CRefVector3D scale) { this->scale = scale; }

		// Modifiers
		void Translate(CRefVector3D distance, const TransformSpace& ts);
		void Rotate(CRefVector3D eulerAngles, const TransformSpace& ts);
		void Scale(CRefVector3D scale, const TransformSpace& ts);

		// In degrees
		void Yaw(float degrees, const TransformSpace& ts);
		void Pitch(float degrees, const TransformSpace& ts);
		void Roll(float degrees, const TransformSpace& ts);

		Core::Vector3D Forward();
		Core::Vector3D Right();
		Core::Vector3D Up();

	private:

		Core::Vector3D position;
		Core::Vector3D scale{ 1, 1, 1 };
		Core::Quaternion orientation{};

		Ogre::SceneNode* entityNode{};

		Transform* parentTr{};
	};

}