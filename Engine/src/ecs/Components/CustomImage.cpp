#include "CustomImage.h"
#include "Entity.h"
#include "Transform.h"

#include <ResourcesManager.h>
#include <RendererManager.h>
#include <ConsoleManager.h>
#include <SDL_image.h>
#include <Texture.h>
#include <algorithm>

ECS::CustomImage::CustomImage(CRefString fileName) : fileName(fileName) {}

void ECS::CustomImage::Init()
{
	renderer = Renderer::RendererManager::Instance()->GetRenderer();

	transform = GetEntity()->GetComponent<Transform>();

	if (transform == nullptr)
	{
		Console::Output::PrintError("Missing transform", "The entity must contain a transform component.");
		this->active = false;
		return;
	}

	if (!fileName.empty())
		LoadTexture(fileName);
}

void ECS::CustomImage::Render()
{
	if (!texture)
		return;

 	for (auto& v : vertex)
	{
 		Vector2D localPos = { v.tex_coord.x * texture->GetWidth() - texture->GetWidth() / 2.f, v.tex_coord.y * texture->GetHeight() - texture->GetHeight() / 2.f };
		localPos *= transform->GetWorldScale();

		float radians = (-transform->GetWorldRotation()) * (M_PI / 180.f);
		float cos_r = cosf(radians);
		float sin_r = sinf(radians);
		float x_rot = localPos.GetX() * cos_r - localPos.GetY() * sin_r;
		float y_rot = localPos.GetX() * sin_r + localPos.GetY() * cos_r;

		Vector2D worldPos = { x_rot + transform->GetWorldPosition().GetX(), y_rot + transform->GetWorldPosition().GetY() };

		int x = worldPos.GetX();
		int y = worldPos.GetY();
		Renderer::RendererManager::Instance()->AdjustRectToCamera(&x, &y, nullptr, nullptr, scrollFactor);
		v.position.x = x;
		v.position.y = y;
	}
	
	SDL_RenderGeometry(renderer, texture->GetSDLTexture(), vertex.data(), vertex.size(), indices.data(), indices.size());
}

int ECS::CustomImage::GetTextureWidth() const
{
	return texture->GetWidth();
}

int ECS::CustomImage::GetTextureHeight() const
{
	return texture->GetHeight();
}

void ECS::CustomImage::SetVertex(const vector<Vector2D>& uvs, const vector<int>& indices)
{
	this->indices = indices;

	vertex.clear();
	vertex.reserve(vertex.size());

	for (const auto & sV : uvs)
		vertex.push_back({ {}, {255, 255, 255, 255}, {sV.GetX(), sV.GetY()} }); // Position, Color, Text coords
}

void ECS::CustomImage::LoadTexture(CRefString texturePath)
{
	fileName = texturePath;
	texture = Resources::ResourcesManager::Instance()->AddTexture(fileName);

	vector<Vector2D> vertex;
	vertex.emplace_back(0.5f, 0.0f);
	vertex.emplace_back(0.0f, 1.0f);
	vertex.emplace_back(1.0f, 1.0f);

	SetVertex(vertex);
}