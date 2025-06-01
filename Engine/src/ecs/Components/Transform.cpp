#include "Transform.h"
#include "Vector2D.h"

#include "Entity.h"

namespace ECS {

	Transform::Transform(CRefVector2 position, CRefVector2 scale, float rotation) :
		localPosition(position), localScale(scale), localRotation(rotation) {}

	void Transform::OnDestroy()
	{
		if (parent != nullptr)
			parent->RemoveChildren(this);
	}

	Utilities::Vector2D Transform::GetWorldPosition()
	{
		if (parent != nullptr)
		{
			Utilities::Vector2D rotatedPosition = GetLocalPosition().Rotate(parent->GetWorldRotation());
			Utilities::Vector2D parentWorldPos = parent->GetWorldPosition();

			return Utilities::Vector2D{ parentWorldPos.GetX() + rotatedPosition.GetX(), parentWorldPos.GetY() + rotatedPosition.GetY() };
		}

		return localPosition;
	}

	void Transform::SetWorldPosition(CRefVector2 position)
	{
		if (parent != nullptr)
		{
			Utilities::Vector2D newPos = { position - parent->GetWorldPosition() };
			newPos = newPos.Rotate(-parent->GetWorldRotation());

			this->localPosition = newPos;

			return;
		}

		this->localPosition = position;
	}

	Utilities::Vector2D Transform::GetWorldScale()
	{
		if (parent != nullptr)
			return localScale.Mult(parent->GetWorldScale());

		return localScale;
	}

	void Transform::SetWorldScale(CRefVector2 scale)
	{
		if (parent != nullptr) {

			auto parentWorldScale = parent->GetWorldScale();
			this->localScale.x_ = scale.x_ / parentWorldScale.x_;
			this->localScale.y_ = scale.y_ / parentWorldScale.y_;
			return;
		}

		this->localScale = scale;
	}

	float Transform::GetWorldRotation()
	{
		if (parent != nullptr)
			return localRotation + parent->GetWorldRotation();

		return localRotation;
	}

	void Transform::SetWorldRotation(float rotation)
	{
		if (parent != nullptr) {

			this->localRotation = rotation - parent->GetWorldRotation();
			return;
		}

		this->localRotation = rotation;
	}

	void Transform::RotateTowards(CRefVector2 position)
	{
		Utilities::Vector2D dif = position - this->GetWorldPosition();

		if (dif.x_ == 0 && dif.y_ == 0) {

			this->SetWorldRotation(0);
			return;
		}

		dif = dif.Normalize();

		float rotation = std::atan2(dif.y_, dif.x_) * -(180.0 / 3.141592653589793238463);

		this->SetWorldRotation(rotation);
	}

	void Transform::SetParent(Transform* tr, bool adjustToParent)
	{
		localPosition = GetWorldPosition();
		localScale = GetWorldScale();
		localRotation = GetWorldRotation();

		if (parent != nullptr) {
			parent->RemoveChildren(this);
		}

		parent = tr;
		if (tr != nullptr && adjustToParent) {
			tr->AddChildren(this);
			SetTransformRelativeToNewParent();
		}
	}

	void Transform::SetTransformRelativeToNewParent()
	{
		Utilities::Vector2D parentPos = parent->GetWorldPosition();
		Utilities::Vector2D newPos = { GetLocalPosition().GetX() - parentPos.GetX(), GetLocalPosition().GetY() - parentPos.GetY() };

		//Tiene sentido
		newPos = newPos.Rotate(-parent->GetWorldRotation());

		SetLocalPosition(newPos);

		float parentRot = parent->GetWorldRotation();
		float newRot = GetLocalRotation() - parentRot;

		SetLocalRotation(newRot);

		Utilities::Vector2D parentScale = parent->GetWorldScale();
		Utilities::Vector2D newScale = { GetLocalScale().GetX() / parentScale.GetX(), GetLocalScale().GetY() / parentScale.GetY() };

		SetLocalScale(newScale);
	}
}