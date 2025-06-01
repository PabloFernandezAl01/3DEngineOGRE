#include "EdgeBody.h"
#include "box2d/b2_world.h"
#include "box2d/b2_edge_shape.h"
#include "Entity.h"
#include "Image.h"
#include "Transform.h"

namespace ECS {

	void EdgeBody::Init()
	{
		PhysicBody::Init();

		shape = new b2EdgeShape();

		Image* image = this->GetEntity()->GetComponent<Image>();

		// Collider radius = max between imagen width and height if exists
		if (image != nullptr) {
			if (size == 0) {
				if (xAxis)
					size = image->GetTextureWidth() / screenToWorldFactor;
				else
					size = image->GetTextureHeight() / screenToWorldFactor;
			}
		}

		ScaleShape();

		shape->m_vertex1 = vertex1;
		shape->m_vertex2 = vertex2;

		bodyDef->type = b2_staticBody;
		bodyDef->position.Set(0, 0);
		bodyDef->userData.pointer = uintptr_t(static_cast<void*>(this));

		fixtureDef->shape = shape;
		fixtureDef->density = 1.0f;
		fixtureDef->isSensor = false;

		body = world->CreateBody(bodyDef);
		fixture = body->CreateFixture(fixtureDef);

		delete shape;

		shape = static_cast<b2EdgeShape*>(fixture->GetShape());
	}

	void EdgeBody::SetEdgeVertices(const Vector2D& v1, const Vector2D& v2) 
	{
		vertex1.x = v1.GetX(); vertex1.y = v1.GetY();
		vertex2.x = v2.GetX(); vertex2.y = v2.GetY();

		shape->m_vertex1 = vertex1;
		shape->m_vertex2 = vertex2;
	}

	void EdgeBody::ScaleShape() 
	{
		auto scale = transform->GetWorldScale();

		if (xAxis) {
			shape->m_vertex1 = { -size / 2 * scale.GetX(), 0 };
			shape->m_vertex2 = { size / 2 * scale.GetX(), 0 };
		}
		else {
			shape->m_vertex1 = { 0, -size / 2 * scale.GetY() };
			shape->m_vertex2 = { 0, size / 2 * scale.GetY() };
		}
	}
}
