#pragma once

#include "ETypes.h"
#include "PhysicBody.h"
#include <vector>

struct b2Vec2;

namespace ECS {

	class CustomBody : public PhysicBody
	{
	public:

		CustomBody();

		void Init() override;

		void SetMass(float mass) override;

		inline float GetArea() override { return CalculatePolygonArea(); }

		// Vertex is in screen units (pixels)
		void SetVertex(const std::vector<Vector2D>& vertex);

	private:

		void ScaleShape() override;

		void RecreateFixture();

		float CalculatePolygonArea();

		// Points is in world units
		std::vector<b2Vec2> points;

	};

}


