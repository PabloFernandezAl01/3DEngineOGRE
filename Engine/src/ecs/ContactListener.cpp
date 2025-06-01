#include "ContactListener.h"
#include <PhysicsManager.h>
#include <box2d/b2_contact.h>
#include "Components/PhysicBody.h"
#include <Entity.h>

namespace ECS {

	ContactListener::ContactListener() {

		Physics::PhysicsManager::Instance()->SetContactListener(this);
	}

	void ContactListener::BeginContact(b2Contact* contact) 
	{

		unsigned int* punteroA = (unsigned int*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
		unsigned int* punteroB = (unsigned int*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

		PhysicBody* phyA = static_cast<PhysicBody*>(static_cast<void*>(punteroA));
		PhysicBody* phyB = static_cast<PhysicBody*>(static_cast<void*>(punteroB));

		if (phyA == nullptr || phyB == nullptr) return;

		auto entA = phyA->GetEntity();
		auto entB = phyB->GetEntity();

		if (entA == nullptr || entB == nullptr) return;

		phyA->SetBox2DContact(contact);
		phyB->SetBox2DContact(contact);

		if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()) 
		{
			entA->OnTriggerEnter(entB);
			entB->OnTriggerEnter(entA);

			phyA->SetTriggerStay(true, entB);
			phyB->SetTriggerStay(true, entA);
		}
		else 
		{
			entA->OnCollisionEnter(entB);
			entB->OnCollisionEnter(entA);

			phyA->SetCollisionStay(true, entB);
			phyB->SetCollisionStay(true, entA);
		}

	}

	void ContactListener::EndContact(b2Contact* contact) 
	{

		unsigned int* punteroA = (unsigned int*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
		unsigned int* punteroB = (unsigned int*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

		PhysicBody* phyA = static_cast<PhysicBody*>(static_cast<void*>(punteroA));
		PhysicBody* phyB = static_cast<PhysicBody*>(static_cast<void*>(punteroB));

		if (phyA == nullptr || phyB == nullptr) return;

		auto entA = phyA->GetEntity();
		auto entB = phyB->GetEntity();

		if (entA == nullptr || entB == nullptr) return;

		phyA->SetBox2DContact(contact);
		phyB->SetBox2DContact(contact);

		if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()) 
		{
			entA->OnTriggerExit(entB);
			entB->OnTriggerExit(entA);

			phyA->SetTriggerStay(false, entB);
			phyB->SetTriggerStay(false, entA);
		}
		else 
		{
			entA->OnCollisionExit(entB);
			entB->OnCollisionExit(entA);

			phyA->SetCollisionStay(false, entB);
			phyB->SetCollisionStay(false, entA);
		}

	}

	void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		b2Fixture* fA = contact->GetFixtureA();
		b2Fixture* fB = contact->GetFixtureB();
		b2Body* bodyA = fA->GetBody();
		b2Body* bodyB = fB->GetBody();

		float maxImpulse = 0.0f;
		for (int i = 0; i < impulse->count; ++i)
			maxImpulse = b2Max(maxImpulse, impulse->normalImpulses[i]);

		unsigned int* punteroA = (unsigned int*)bodyA->GetUserData().pointer;
		unsigned int* punteroB = (unsigned int*)bodyB->GetUserData().pointer;

		PhysicBody* phyA = static_cast<PhysicBody*>(static_cast<void*>(punteroA));
		PhysicBody* phyB = static_cast<PhysicBody*>(static_cast<void*>(punteroB));

		if (phyA == nullptr || phyB == nullptr) return;

		auto* entA = phyA->GetEntity();
		auto* entB = phyB->GetEntity();

		if (entA == nullptr || entB == nullptr) return;

		if (!fA->IsSensor() && !fB->IsSensor())
		{
			entA->OnPostSolve(entB, maxImpulse);
			entB->OnPostSolve(entA, maxImpulse);
		}
	}

}