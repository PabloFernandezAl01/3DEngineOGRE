#include "Breakable.h"

#include <Components/CustomBody.h>
#include <Components/Transform.h>
#include <Prefabs/BreakSlice.h>
#include <Components/BoxBody.h>
#include <Components/Image.h>
#include <ConsoleManager.h>
#include <PhysicsManager.h>
#include <InputManager.h>
#include <Entity.h>
#include <Scene.h>
#include <random>

#define JC_VORONOI_IMPLEMENTATION
#include <jc_voronoi.h>

using namespace Utilities;

void ECS::Breakable::Init()
{
	tr = GetEntity()->GetComponent<Transform>();

	if (tr == nullptr)
	{
		Console::Output::PrintError("Missing transform", "The entity must contain a transform component.");
		this->active = false;
		return;
	}

	img = GetEntity()->GetComponent<Image>();
}

void ECS::Breakable::OnPostSolve(Entity* b, float normalImpulse)
{
	if (normalImpulse < impactDeadzone)
		return;

	life -= normalImpulse;

	if (life <= 0 && !entity->IsRemoved())
	{
		Break();
	}
}

void ECS::Breakable::Break()
{
	Vector2D size = { (float)img->GetTextureWidth(), (float)img->GetTextureHeight() };

	// RECT
	jcv_rect rect{ { -size.GetX() / 2.f, -size.GetY() / 2.f}, 
					size.GetX() / 2.f, size.GetY() / 2.f };


	// JCV POINTS
	GeneratePointsInRectangle();
	std::vector<jcv_point> jcv_points;
	jcv_points.reserve(points.size());
	for (const auto& p : points)
		jcv_points.push_back({ p.GetX(), p.GetY() });

	// POINTS RELAXATION
	for (int i = 0; i < nRelaxations; ++i)
	{
		jcv_diagram diagram{};
		jcv_diagram_generate(nPoints, jcv_points.data(), &rect, nullptr, &diagram);

		RelaxPoints(&diagram, jcv_points.data());

		jcv_diagram_free(&diagram);
	}

	// GENERATE
	jcv_diagram diagram{};
	jcv_diagram_generate(nPoints, jcv_points.data(), &rect, nullptr, &diagram);

	// SITES
	const jcv_site* sites = jcv_diagram_get_sites(&diagram);

	for (int i = 0; i < nPoints; ++i)
	{
		const jcv_site* site = &sites[i];
		const jcv_graphedge* edge = site->edges;

		std::vector<Vector2D> polygon;

		while (edge)
		{
			polygon.emplace_back(edge->pos[0].x, edge->pos[0].y);
			edge = edge->next;
		}

		// Box2D allows polygon shapes with vertex between 3 and 8
		if (polygon.size() >= 3 && polygon.size() <= 8)
			CreatePolygon(polygon);
	}

	GetScene()->RemoveEntity(entity);

	// FREE DIAGRAM
	jcv_diagram_free(&diagram);
}

void ECS::Breakable::CreatePolygon(const std::vector<Vector2D>& poly)
{
	auto* breakSlice = GetScene()->Instantiate<BreakSlice>("Break Slice", entity->GetRenderOrder());

	breakSlice->SetLifeSpan(breakSliceLifeSpan);

	breakSlice->SetVertex(poly);
	breakSlice->SetOriginalTexture(img->GetTexture());

	breakSlice->SetPhysicsLayer(layerName);

	Vector2D size = { (float)img->GetTextureWidth(), (float)img->GetTextureHeight() };
	Vector2D rectLU = { -size.GetX() / 2.f, -size.GetY() / 2.f };
	breakSlice->SetOriginalRectangle(rectLU, size);

	// Transform
	breakSlice->SetOriginalPosition(tr->GetWorldPosition());
	breakSlice->SetOriginalRotation(tr->GetWorldRotation());
	breakSlice->SetOriginalScale(tr->GetWorldScale());
}

void ECS::Breakable::GeneratePointsInRectangle()
{
	Vector2D size = { (float)img->GetTextureWidth(), (float)img->GetTextureHeight() };

	points.reserve(nPoints);

	float halfWidth = size.GetX() / 2.0f;
	float halfHeight = size.GetY() / 2.0f;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distX(-halfWidth, halfWidth);
	std::uniform_real_distribution<float> distY(-halfHeight, halfHeight);

	for (int i = 0; i < nPoints; ++i) {
		float x = distX(gen);
		float y = distY(gen);
		points.emplace_back(x, y);
	}
}

void ECS::Breakable::RelaxPoints(const jcv_diagram* diagram, jcv_point* points)
{
	const jcv_site* sites = jcv_diagram_get_sites(diagram);
	for (int i = 0; i < diagram->numsites; ++i)
	{
		const jcv_site* site = &sites[i];
		jcv_point sum = site->p;
		int count = 1;

		const jcv_graphedge* edge = site->edges;

		while (edge)
		{
			sum.x += edge->pos[0].x;
			sum.y += edge->pos[0].y;
			++count;
			edge = edge->next;
		}

		points[site->index].x = sum.x / (jcv_real)count;
		points[site->index].y = sum.y / (jcv_real)count;
	}
}
