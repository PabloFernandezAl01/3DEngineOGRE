#include "TopDownController.h"
#include "ConsoleManager.h"
#include "InputManager.h"
#include "CircleBody.h"
#include "Transform.h"
#include "BoxBody.h"
#include "Entity.h"

#include <Vector2D.h>

namespace ECS {

	void TopDownController::Init() 
	{
		im = Input::InputManager::Instance();

		transform = this->GetEntity()->GetComponent<Transform>();

		if (transform == nullptr) 
		{
			Console::Output::PrintError("Missing transform", "The entity must contain a transform component.");
			this->active;
			return;
		}

		if (usePhysics) 
		{
			BoxBody* bBody = this->GetEntity()->GetComponent<BoxBody>();
			CircleBody* cBody = this->GetEntity()->GetComponent<CircleBody>();

			if (bBody == nullptr && cBody == nullptr) 
			{
				Console::Output::PrintError("Missing physic body (Circle o Box)", "The entity must contain a physical body in case you want it to move with physics.");
				this->active;
				return;
			}

			if (bBody != nullptr)
				body = bBody;
			else if (cBody != nullptr)
				body = cBody;
		}

	}

	void TopDownController::Update(float dt) 
	{
		if (blockXAxis)
			direction = { 0, im->VerticalMovement() };
		else if (blockYAxis)
			direction = { im->HorizontalMovement(), 0 };
		else
			direction = { im->HorizontalMovement(), im->VerticalMovement() };

		if (clampDiagonalVelocity)
			direction = direction.Normalize();

		if (usePhysics) return;

		transform->Translate(direction * dt * velocity);
	}

	void TopDownController::FixedUpdate(float fixedDt)
	{
		if (!usePhysics) return;
		
		body->SetLinearVelocity(direction.GetX() * fixedDt * velocity, direction.GetY() * fixedDt * velocity);
	}
}