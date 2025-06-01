#pragma once

#include "Component.h"

#include <ETypes.h>
#include <list>

namespace ECS {

	class Transform : public Component {
	public:

		Transform() {};
		Transform(CRefVector2D position, CRefVector2D scale, float rotation);

		// World position
		inline CRefVector2D GetPosition() { return position; }
		inline void SetPosition(CRefVector2D position) { this->position = position; }

		// World rotation
		inline float GetRotation() { return rotation; }
		inline void SetRotation(float rotation) { this->rotation = rotation; }

		// World scale
		inline CRefVector2D GetScale() { return scale; }
		inline void SetScale(CRefVector2D scale) { this->scale = scale; }

		// Modifiers
		inline void Translate(CRefVector2D distance) { this->position += distance; }
		inline void Rotate(float rotation) { this->rotation += rotation; }
		inline void Scale(float scale) { this->scale.x_ += scale; this->scale.y_ += scale; }

	private:

		Core::Vector2D position;
		Core::Vector2D scale{ 1, 1 };
		double rotation{};
	};

}