#pragma once

#include <Vector2D.h>
#include "box2d/box2d.h"

namespace Physics
{
	struct RayCastInput
	{
		Utilities::Vector2D p1, p2;
		float maxFraction;
	};

	struct RayCastOutput
	{
		Utilities::Vector2D normal;
		float fraction;
	};

	class RayCastClosestCallback : public b2RayCastCallback 
	{
	public:
		bool hit = false;
		b2Vec2 point;
		b2Vec2 normal;
		float fraction = 0.0f;

		float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override
		{
			this->hit = true;
			this->point = point;
			this->normal = normal;
			this->fraction = fraction;
			return fraction; 
		}
	};

}
