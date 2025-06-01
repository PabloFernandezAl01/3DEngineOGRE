#include "AtlasImage.h"
#include <SDL_image.h>
#include "TargetTexture.h"
#include <ResourcesManager.h>
#include <RendererManager.h>
#include <Texture.h>
#include "Transform.h"
#include "Entity.h"
#include <ConsoleManager.h>

using namespace Renderer;

ECS::AtlasImage::AtlasImage(vector<Atlas>& atlas, int width, int height) : atlas(atlas), width(width), height(height){}

ECS::AtlasImage::~AtlasImage()
{
	delete targetTexture;
}

void ECS::AtlasImage::Init()
{
	renderer = Renderer::RendererManager::Instance()->GetRenderer();

	transform = GetEntity()->GetComponent<Transform>();

	if (transform == nullptr)
	{
		Console::Output::PrintError("Missing transform", "The entity must contain a transform component.");
		this->active = false;
		return;
	}

	targetTexture = new TargetTexture(width, height);

	BuildTexture();
}

void ECS::AtlasImage::Render()
{
	int width = srcRect.w;
	int height = srcRect.h;

	auto trPos = transform->GetWorldPosition();
	auto trScale = transform->GetWorldScale();

	int w = std::round(trScale.GetX() * width);
	int h = std::round(trScale.GetY() * height);

	int x = std::round(trPos.GetX() - w * 0.5f);
	int y = std::round(trPos.GetY() + h * 0.5f);

	Renderer::RendererManager::Instance()->AdjustRectToCamera(&x, &y, &w, &h, scrollFactor);

	dstRect = { x, y, w, h };

	SDL_RenderCopy(renderer, targetTexture->GetSDLTexture(), &srcRect, &dstRect);
}

void ECS::AtlasImage::BuildTexture()
{
	// Load atlas textures
	for (auto& a : atlas)
		if (!a.fileName.empty())
			a.texture = Resources::ResourcesManager::Instance()->AddTexture(a.fileName);

	// Save original render target
	SDL_Texture* originalTarget = SDL_GetRenderTarget(renderer);

	// Set our texture to be the target
	SDL_SetRenderTarget(renderer, targetTexture->GetSDLTexture());

	// Clear the texture
	auto& color = Renderer::RendererManager::Instance()->GetBackgroundColor();
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
	SDL_SetTextureBlendMode(targetTexture->GetSDLTexture(), SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer);

	// Render each src rect in trg rect
	for (const auto& a : atlas)
		for (const auto& r : a.rects)
			SDL_RenderCopyEx(renderer, a.texture->GetSDLTexture(), &r.src, &r.trg, 0, nullptr, (SDL_RendererFlip) r.flipMode);

	// Reder target to original target
	SDL_SetRenderTarget(renderer, originalTarget);

	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = targetTexture->GetTextureWidth();
	srcRect.h = targetTexture->GetTextureHeight();
}
