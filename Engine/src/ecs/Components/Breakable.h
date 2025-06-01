#pragma once

#include "Component.h"
#include "ETypes.h"
#include <vector>

using namespace Utilities;

typedef struct jcv_diagram_ jcv_diagram;
typedef struct jcv_point_ jcv_point;

namespace ECS {

	class Entity;
	class Image;
	class Transform;

	class Breakable : public Component
	{
	public:

		Breakable() = default;

		void Init() override;

		void OnPostSolve(Entity* b, float normalImpulse) override;

		// How resistant the object is 
		inline void SetLife(float life) { this->life = life; }

		inline void SetPhysicsLayer(CRefString layer) { layerName = layer; }

		// Subdivisions lifespan
		inline void SetBreakSlicesLifeSpan(float lifespan) { breakSliceLifeSpan = lifespan; }

		// Impact threshold ignored
		inline void SetImpactDeadzone(float deadzone) { impactDeadzone = deadzone; }

		// Number of subdivisions
		inline void SetVoronoiPoints(int poitns) { nPoints = poitns; }

		// How uniformed distributed the subdivisions are
		inline void SetRelaxations(int relaxations) { nRelaxations = relaxations; }

	private:

		void Break();

		void GeneratePointsInRectangle();

		void CreatePolygon(const std::vector<Vector2D>& polygon);

		void RelaxPoints(const jcv_diagram* diagram, jcv_point* points);

		float life{};
		float breakSliceLifeSpan{};
		float impactDeadzone{};
		std::string layerName;

		Image* img{};
		Transform* tr{};

		// Voronoi settings
		int nPoints{};
		int nRelaxations{};
		std::vector<Vector2D> points;

	};
}

