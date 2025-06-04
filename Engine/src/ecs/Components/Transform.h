#pragma once

#include "Component.h"

#include <ETypes.h>
#include <list>

namespace ECS {

	class Transform : public Component {
	public:

		Transform() {};
		Transform(CRefVector3D position, CRefVector3D scale, CRefQuaternion quaternion);

		void Update(float dt) override;

		// World position
		inline CRefVector3D GetPosition() { return position; }
		inline void SetPosition(CRefVector3D position) { this->position = position; }

		// World rotation
		inline CRefQuaternion GetRotation() { return rotation; }
		inline void SetRotation(CRefQuaternion rotation) { this->rotation = rotation; }

		// World scale
		inline CRefVector3D GetScale() { return scale; }
		inline void SetScale(CRefVector3D scale) { this->scale = scale; }

		// Modifiers
		inline void Translate(CRefVector3D distance) { this->position += distance; }
		inline void Rotate(CRefVector3D eulerAngles) { this->rotation.Rotate(eulerAngles); }
		inline void Scale(CRefVector3D scale) { this->scale += scale; }

		void LookAt(CRefVector3D direction);

	private:

		Core::Vector3D position;
		Core::Vector3D scale{ 1, 1, 1 };
		Core::Quaternion rotation{};
	};

}