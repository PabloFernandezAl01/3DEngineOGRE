#include "CircleBody.h"
#include "PhysicsManager.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_world.h"
#include "Entity.h"
#include "Image.h"
#include "Transform.h"

namespace ECS {

	void CircleBody::Init() 
	{
		PhysicBody::Init();

		b2CircleShape shape;

		Image* image = this->GetEntity()->GetComponent<Image>();

		// Collider radius = max between imagen width and height if exists
		if (image != nullptr && image->HasLoadedTexture()) {

			Utilities::Vector2D imageSize = { (image->GetTextureWidth() / screenToWorldFactor) * transform->GetWorldScale().GetX(),
											(image->GetTextureHeight() / screenToWorldFactor) * transform->GetWorldScale().GetY() };

			radius = std::min(imageSize.GetX(), imageSize.GetY()) / 2;
		}

		shape.m_radius = radius;

		bodyDef->type = b2_staticBody;
		bodyDef->position.Set(0, 0);
		bodyDef->userData.pointer = uintptr_t(static_cast<void*>(this));

		fixtureDef->shape = &shape;
		fixtureDef->density = mass / GetArea();
		fixtureDef->isSensor = false;

		body = world->CreateBody(bodyDef);
		fixture = body->CreateFixture(fixtureDef);

		// Collision Filtering
		b2Filter filter = fixture->GetFilterData();

		filter.categoryBits = pm->GetLayerBits(layerName);
		filter.maskBits = pm->GetMaskBits(layerName);

		fixture->SetFilterData(filter);
	}

	void CircleBody::SetMass(float mass)
	{
		this->mass = mass;

		fixture->SetDensity(mass / GetArea());

		body->ResetMassData();
	}

	void CircleBody::SetRadius(float radius) 
	{
		this->radius = radius;

		RecreateFixture();
	}

	void CircleBody::ScaleShape()
	{
		float scaledX = radius * transform->GetWorldScale().GetX();
		float scaledY = radius * transform->GetWorldScale().GetY();
		radius = std::min(scaledX, scaledY) / 2;

		RecreateFixture();
	}

	void CircleBody::RecreateFixture()
	{
		body->DestroyFixture(fixture);
		b2CircleShape newShape;
		newShape.m_radius = radius;

		fixtureDef->shape = &newShape;
		fixtureDef->density = mass / GetArea();
		fixtureDef->isSensor = false;

		fixture = body->CreateFixture(fixtureDef);

		// Collision Filtering
		b2Filter filter = fixture->GetFilterData();

		filter.categoryBits = pm->GetLayerBits(layerName);
		filter.maskBits = pm->GetMaskBits(layerName);

		fixture->SetFilterData(filter);

		body->ResetMassData();
	}

}
