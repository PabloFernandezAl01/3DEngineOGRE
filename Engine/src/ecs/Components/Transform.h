#pragma once

#include "Component.h"

#include <ETypes.h>
#include <list>

namespace ECS {

	class Transform : public Component {
	public:

		Transform() {};
		Transform(CRefVector2D position, CRefVector2D scale, float rotation);

		void OnDestroy() override;

		// Local position
		inline CRefVector2D GetLocalPosition() { return localPosition; }
		inline void SetLocalPosition(CRefVector2D position) { this->localPosition = position; }
		inline void SetLocalPositionX(float x) { this->localPosition.Set(x, localPosition.GetY()); }
		inline void SetLocalPositionY(float y) { this->localPosition.Set(localPosition.GetX(), y); }

		// Local scale
		inline CRefVector2D GetLocalScale() { return localScale; }
		inline void SetLocalScale(CRefVector2D scale) { this->localScale = scale; }
		inline void SetScaleX(float x) { this->localScale.Set(x, localScale.GetY()); }
		inline void SetScaleY(float y) { this->localScale.Set(y, localScale.GetX()); }

		// Local rotation
		const double& GetLocalRotation() { return localRotation; }
		inline void SetLocalRotation(float rotation) { this->localRotation = rotation; }

		
		// World position
		Core::Vector2D GetWorldPosition();
		void SetWorldPosition(CRefVector2D position);

		// World scale
		Core::Vector2D GetWorldScale();
		void SetWorldScale(CRefVector2D scale);

		// World rotation
		float GetWorldRotation();
		void SetWorldRotation(float rotation);


		// Modifiers
		inline void Translate(CRefVector2D distance) { this->localPosition += distance; }
		inline void TranslateX(float distanceX) { this->localPosition.Set(this->localPosition.GetX() + distanceX, this->localPosition.GetY()); }
		inline void TranslateY(float distanceY) { this->localPosition.Set(this->localPosition.GetX(), this->localPosition.GetY() + distanceY); }

		void RotateTowards(CRefVector2D position);
		inline void Rotate(float rotation) { this->localRotation += rotation; }

		inline void Scale(float scale) { this->localScale.x_ += scale; this->localScale.y_ += scale; }

		void SetParent(Transform* tr, bool adjustToParent = true);
		void SetTransformRelativeToNewParent();

	private:

		inline void AddChildren(Transform* tr) { children.push_back(tr); }
		inline void RemoveChildren(Transform* tr) { children.remove(tr); }

	private:

		Core::Vector2D localPosition{};
		Core::Vector2D localScale{ 1, 1 };
		double localRotation{};

		Transform* parent{};
		std::list<Transform*> children;
	};

}