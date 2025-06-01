#include "BoxBody.h"
#include "PhysicsManager.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "Entity.h"
#include "Image.h"
#include "Transform.h"

namespace ECS {

	void BoxBody::Init() 
	{
		PhysicBody::Init();

		b2PolygonShape shape{};

		Image* image = this->GetEntity()->GetComponent<Image>();

		// Collider size = Image size if Image component exists in the entity
		if (image != nullptr && image->HasLoadedTexture())
		{
			Utilities::Vector2D imageSize = { (image->GetTextureWidth() / screenToWorldFactor) * transform->GetWorldScale().GetX(),
											(image->GetTextureHeight() / screenToWorldFactor)* transform->GetWorldScale().GetY() };

			if (size.GetX() == 0 || size.GetY() == 0)
				size.Set(imageSize);
		}

		shape.SetAsBox(size.GetX() / 2.f, size.GetY() / 2.f);

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

	void BoxBody::SetMass(float mass) 
	{
		this->mass = mass;

		fixture->SetDensity(mass / GetArea());
		body->ResetMassData();
	}

	void BoxBody::SetSize(CRefVector2 size)
	{
		this->size.Set(size.GetX() / screenToWorldFactor, size.GetY() / screenToWorldFactor);

		RecreateFixture();
	}

	void BoxBody::ScaleShape() 
	{
		// Scale
		size.SetX(size.GetX() * transform->GetWorldScale().GetX());
		size.SetY(size.GetY() * transform->GetWorldScale().GetY());

		RecreateFixture();
	}

	void BoxBody::RecreateFixture()
	{
		body->DestroyFixture(fixture);
		b2PolygonShape newShape;
		newShape.SetAsBox(size.GetX() / 2.f, size.GetY() / 2.f);

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
