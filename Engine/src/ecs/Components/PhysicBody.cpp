#include "PhysicBody.h"
#include "PhysicsManager.h"
#include "box2d/b2_world.h"
#include "box2d/b2_contact.h"
#include "Transform.h"
#include "BoxBody.h"
#include "CircleBody.h"
#include "EdgeBody.h"

#include <ConsoleManager.h>
#include <Entity.h>

namespace ECS {

	PhysicBody::PhysicBody() 
	{
		pm = PhysicsManager::Instance();

		screenToWorldFactor = pm->GetScreenToWorldFactor();

		layerName = "Default";
	}

	PhysicBody::~PhysicBody() 
	{
		delete bodyDef;
		delete fixtureDef;
	}

	void PhysicBody::OnDestroy() 
	{
		world->DestroyBody(body);
	}

	void PhysicBody::Init() 
	{
		transform = this->GetEntity()->GetComponent<Transform>();

		if (transform == nullptr) 
		{
			Console::Output::PrintError("Missing transform", "The entity must contain a transform component.");
			this->active = false;
			return;
		}

		world = pm->GetWorld();

		bodyDef = new b2BodyDef();
		fixtureDef = new b2FixtureDef();
	}

	void PhysicBody::Start() 
	{
		auto position = transform->GetWorldPosition();
		auto rotation = -transform->GetWorldRotation();
		auto scale = transform->GetWorldScale();

		// Radians
		float radians = (b2_pi / 180) * (rotation);

		Vector2D v = Vector2D(offSet.GetX() * std::cos(radians) - offSet.GetY() * std::sin(radians), offSet.GetX() * std::sin(radians) + offSet.GetY() * std::cos(radians));

		Vector2D p = { position.GetX() + v.GetX(), position.GetY() + v.GetY() };
		p = p / screenToWorldFactor;

		// Position + rotation
		body->SetTransform({p.GetX(), p.GetY()}, radians);

		ScaleShape();

		lastPositionSync = position;
		lastRotationSync = rotation;
		lastScaleInfo = scale;

		// Collision Filtering
		b2Filter filter = fixture->GetFilterData();

		filter.categoryBits = pm->GetLayerBits(layerName);
		filter.maskBits = pm->GetMaskBits(layerName);

		fixture->SetFilterData(filter);

		// Fixture and body attributes
		SetBodyType(bodyType);
		SetBounciness(bounciness);
		SetTrigger(trigger);
		SetRotationFreezed(freezeRotation);
		SetGravityScale(gravityScale);
		SetFriction(friction);
		SetLinearDrag(linearDamping);
		SetAngularDrag(angularDamping);
	}

	void PhysicBody::FixedUpdate(float fixedDeltaTime) 
	{
		auto position = transform->GetWorldPosition();
		auto rotation = -transform->GetWorldRotation();
		auto scale = transform->GetWorldScale();

		if (onCollisonStay)
			GetEntity()->OnCollisionStay(collisionEntity);
		if (onTriggerStay)
			GetEntity()->OnTriggerStay(collisionEntity);

		// Position
		Vector2D trPosOffSet = position - lastPositionSync;

		Vector2D bodyPosOffSet = { body->GetPosition().x * screenToWorldFactor - offSet.GetX() - lastPositionSync.GetX(),
									body->GetPosition().y * screenToWorldFactor - offSet.GetY() - lastPositionSync.GetY()};

		Vector2D newPos = lastPositionSync + trPosOffSet + bodyPosOffSet;

		lastPositionSync = newPos;

		// Rotation
		float trRotOffSet = rotation - lastRotationSync;

		float bodyRotOffSet = body->GetAngle() * (180 / b2_pi) - lastRotationSync;

		float newRotation = lastRotationSync + trRotOffSet + bodyRotOffSet;

		lastRotationSync = newRotation;

		// Scale
		if (lastScaleInfo != scale) {
			ScaleShape();
			lastScaleInfo = scale;
		}

		// Body
		body->SetTransform(b2Vec2(newPos.GetX() / screenToWorldFactor + offSet.GetX() / screenToWorldFactor, 
			newPos.GetY() / screenToWorldFactor + offSet.GetY() / screenToWorldFactor), newRotation * (b2_pi / 180));

		// Transform
		transform->SetWorldPosition(newPos);
		transform->SetWorldRotation(-newRotation);
	}

	void PhysicBody::OnActive() 
	{
		pm->SetBodyEnabled(body, true);
	}

	void PhysicBody::OnDeacitve() 
	{
		pm->SetBodyEnabled(body, false);
	}

	void PhysicBody::OnSceneUp() 
	{
		pm->SetBodyEnabled(body, true);
	}

	void PhysicBody::OnSceneDown() 
	{
		pm->SetBodyEnabled(body, false);
	}

	PhysicBody* PhysicBody::GetComponentFromEntity(Entity* ent) 
	{
		PhysicBody* other = ent->GetComponent<BoxBody>();

		if (other == nullptr)
			other = ent->GetComponent<CircleBody>();

		if (other == nullptr)
			other = ent->GetComponent<EdgeBody>();

		return other;
	}

	void PhysicBody::SetBodyType(const BODY_TYPE& type)
	{
		bodyType = type;

		b2BodyType t = b2_staticBody;

		switch (type) 
		{
		case BODY_TYPE::STATIC:
			t = b2_staticBody;
			break;
		case BODY_TYPE::KINEMATIC:
			t = b2_kinematicBody;
			break;
		case BODY_TYPE::DYNAMIC:
			t = b2_dynamicBody;
			break;
		default:
			break;
		}

		body->SetType(t);
	}

	void PhysicBody::SetCollisionLayer(CRefString layerName)
	{
		if (!pm->LayersExists(layerName)) 
		{
			Console::Output::PrintError("Physics Body", "The layer with name " + layerName + " does not exist.");
			return;
		}

		this->layerName = layerName;
	}

	void PhysicBody::SetCollisionStay(bool stay, Entity* b) 
	{
		onCollisonStay = stay;
		this->collisionEntity = b;
	}

	void PhysicBody::SetTriggerStay(bool stay, Entity* b) 
	{
		onTriggerStay = stay;
		this->collisionEntity = b;
	}

	void PhysicBody::SetBox2DContact(b2Contact* c) 
	{
		this->contact = c;

		// Local Normal
		collisionNormal.Set(this->contact->GetManifold()->localNormal.x, this->contact->GetManifold()->localNormal.y);

		// Local Point
		collisionPoint.Set(this->contact->GetManifold()->localPoint.x, this->contact->GetManifold()->localPoint.y);
	}

	bool PhysicBody::CollidesWith(PhysicBody* b) const
	{
		return pm->LayersCollide(layerName, b->GetCollisionLayer());
	}

	void PhysicBody::ApplyForce(CRefVector2 force, CRefVector2 point)
	{
		body->ApplyForce({ force.GetX(), force.GetY() }, { point.GetX(), point.GetY() }, true);
	}

	void PhysicBody::ApplyForceToCenter(CRefVector2 force)
	{
		body->ApplyForceToCenter({ force.GetX(), force.GetY() }, true);
	}

	void PhysicBody::ApplyTorque(float torque)
	{
		body->ApplyTorque(torque, true);
	}

	void PhysicBody::ApplyLinearImpulse(CRefVector2 impulse, CRefVector2 point)
	{
		body->ApplyLinearImpulse({ impulse.GetX(), impulse.GetY() }, { point.GetX(), point.GetY() }, true);
	}

	void PhysicBody::ApplyLinearImpulseToCenter(CRefVector2 impulse)
	{
		body->ApplyLinearImpulseToCenter({ impulse.GetX(), impulse.GetY() }, true);
	}

	void PhysicBody::ApplyAngularImpulse(float impulse)
	{
		body->ApplyAngularImpulse(impulse, true);
	}

	bool PhysicBody::Raycast(const RayCastInput& input, RayCastOutput* output, int childIndex)
	{
		b2RayCastInput raycastInput{ {input.p1.GetX(), input.p1.GetY()}, {input.p2.GetX(), input.p2.GetY()}, input.maxFraction };
		b2RayCastOutput raycastOutput{};

		bool intersected = fixture->RayCast(&raycastOutput, raycastInput, childIndex);

		output->fraction = raycastOutput.fraction;
		output->normal = { raycastOutput.normal.x, raycastOutput.normal.y };

		return intersected;
	}

}
