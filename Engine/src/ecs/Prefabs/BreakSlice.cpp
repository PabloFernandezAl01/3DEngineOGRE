#include "BreakSlice.h"

#include "Components/Transform.h"
#include "Components/CustomImage.h"
#include "Components/CustomBody.h"

ECS::BreakSlice::BreakSlice(CRefString name, int renderOrder) : Entity(name, renderOrder)
{
	tr = AddComponent<Transform>();
	img = AddComponent<CustomImage>();
	customBody = AddComponent<CustomBody>();
}

void ECS::BreakSlice::Config()
{
	customBody->SetVertex(vertex);
	customBody->SetBodyType(PhysicBody::BODY_TYPE::DYNAMIC);
	customBody->SetCollisionLayer(layerName);

	tr->SetWorldPosition(originalPos);
	tr->SetWorldRotation(originalRotation);
	tr->SetWorldScale(originalScale);

	vector<int> indices{};
	for (int i = 1; i < vertex.size() - 1; ++i) 
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	vector<Vector2D> uvs{};
	for (const auto& v : vertex)
		uvs.emplace_back((v.GetX() - rectLU.GetX()) / rectSize.GetX(), (v.GetY() - rectLU.GetY()) / rectSize.GetY());

	img->SetTexture(texture);
	img->SetVertex(uvs, indices);
}