#include "CustomBody.h"
#include "PhysicsManager.h"
#include "box2d/b2_polygon_shape.h"
#include "Entity.h"
#include "Transform.h"

ECS::CustomBody::CustomBody() 
{
	// Default polygon (triangle)
	points = { { 0, -1 }, { 1, 0 }, { -1, 0 } };
}

void ECS::CustomBody::Init()
{
	PhysicBody::Init();

	b2PolygonShape shape{};

	shape.Set(points.data(), points.size());

	bodyDef->type = b2_staticBody;
	bodyDef->position.Set(0, 0);
	bodyDef->userData.pointer = uintptr_t(static_cast<void*>(this));

	fixtureDef->shape = &shape;
	fixtureDef->density = mass / GetArea();
	fixtureDef->isSensor = false;

	body = world->CreateBody(bodyDef);
	fixture = body->CreateFixture(fixtureDef);
}

void ECS::CustomBody::RecreateFixture()
{
	body->DestroyFixture(fixture);
	b2PolygonShape newShape;
	newShape.Set(points.data(), points.size());

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


void ECS::CustomBody::SetMass(float mass)
{
	this->mass = mass;

	fixture->SetDensity(mass / GetArea());
	body->ResetMassData();
}

void ECS::CustomBody::SetVertex(const std::vector<Vector2D>& vertex)
{
	points.clear();
	points.reserve(vertex.size());

	for (const auto& v : vertex)
		points.emplace_back(v.GetX() / screenToWorldFactor, v.GetY() / screenToWorldFactor); // Convert to world coordinates

	RecreateFixture();
}

void ECS::CustomBody::ScaleShape()
{
	for (auto& p : points)
	{
		p.x *= transform->GetWorldScale().GetX();
		p.y *= transform->GetWorldScale().GetY();
	}

	RecreateFixture();
}

float ECS::CustomBody::CalculatePolygonArea()
{
	int n = points.size();
	if (n < 3) return 0.0f;

	float area = 0.0f;
	for (int i = 0; i < n; ++i) {
		const b2Vec2& p1 = points[i];
		const b2Vec2& p2 = points[(i + 1) % n];

		area += (p1.x * p2.y) - (p2.x * p1.y);
	}

	return std::abs(area) * 0.5f;
}

