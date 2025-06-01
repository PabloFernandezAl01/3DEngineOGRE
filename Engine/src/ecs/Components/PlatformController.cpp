#include "PlatformController.h"
#include "Entity.h"
#include "Transform.h"
#include "BoxBody.h"
#include "CircleBody.h"
#include "EdgeBody.h"

#include "ConsoleManager.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "box2d/b2_contact.h"

namespace ECS {

	void PlatformController::Init() 
	{
		im = Input::InputManager::Instance();

		transform = this->GetEntity()->GetComponent<Transform>();

		if (transform == nullptr) 
		{
			Console::Output::PrintError("Missing transform", "The entity must contain a transform component.");
			this->active = false;
			return;
		}

		BoxBody* bBody = this->GetEntity()->GetComponent<BoxBody>();
		CircleBody* cBody = this->GetEntity()->GetComponent<CircleBody>();

		if (bBody == nullptr && cBody == nullptr) 
		{
			Console::Output::PrintError("Missing physic body (Circle o Box)", "The entity must contain a physical body in case you want it to move with physics.");
			this->active = false;
			return;
		}

		if (bBody != nullptr)
			body = bBody;
		else if (cBody != nullptr)
			body = cBody;

		nJumps = avalaibleJumps;
		platformLayer = body->GetCollisionLayer();
	}

	void PlatformController::Update(float dt) 
	{
		direction = im->HorizontalMovement();

		if (!hasJumped && nJumps > 0 && im->Jump())
		{
			hasJumped = true;
			nJumps--;
		}
	}

	void PlatformController::FixedUpdate(float fixedDt) 
	{
		// Salto
		if (hasJumped) 
		{
			float impulse = body->GetMass() * jumpForce * fixedDt;

			// Eliminar la velocidad actual en Y
			body->SetLinearVelocity(body->GetLinearVelocity().GetX(), 0);

			body->ApplyLinearImpulseToCenter({ 0, impulse });

			hasJumped = false;
		}

		// Movimiento horizontal
		body->ApplyLinearImpulseToCenter({ direction * velocity * fixedDt, 0 });

		auto vel = body->GetLinearVelocity();

		// Limitar velocidad maxima
		if (vel.GetX() > maxVelocity)
			body->SetLinearVelocity(maxVelocity, vel.GetY());
		else if (vel.GetX() < -maxVelocity)
			body->SetLinearVelocity(-maxVelocity, vel.GetY());

		vel = body->GetLinearVelocity();

		// Aplicar damping eje X
		float newX = vel.GetX() * (1 - horizontalDamping);
		vel.SetX(newX);

		body->SetLinearVelocity(vel.GetX(), vel.GetY());
	}

	void PlatformController::OnCollisionEnter(Entity* ent) 
	{
		auto other = PhysicBody::GetComponentFromEntity(ent);

		if (other->GetCollisionLayer() == platformLayer) {

			if (std::abs(body->GetCollisionNormal().GetY()) == 1.0f && body->GetLinearVelocity().GetY() < 0) {
				onGround = true;
				nJumps = avalaibleJumps;
			}
		}
	}

	void PlatformController::OnCollisionExit(Entity* ent) 
	{
		auto other = PhysicBody::GetComponentFromEntity(ent);

		if (other->GetCollisionLayer() == platformLayer) 
		{
			onGround = false;
			hasJumped = false;
		}
	}
}
