#include "Image.h"
#include "Entity.h"
#include "Transform.h"

#include <ResourcesManager.h>
#include <RendererManager.h>
#include <ConsoleManager.h>
#include <SDL_image.h>
#include <Texture.h>

namespace ECS {

	Image::Image(CRefString fileName) : fileName(fileName) {}

	Image::~Image() 
	{
		delete point;
	}

	void Image::Init() 
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

		// Rotation point
		point = new SDL_Point({ 0, 0 });
	}

	void Image::Render()
	{
		if (!texture)
			return;

		srcRect = { srcX, srcY, srcWidth, srcHeight };

		int width = GetTextureWidth();
		int height = GetTextureHeight();

		auto trScale = transform->GetWorldScale();
		auto trPos = transform->GetWorldPosition();

		int w = std::round(trScale.GetX() * width);
		int h = std::round(trScale.GetY() * height);

		int x = std::round(trPos.GetX() - w * 0.5f);
		int y = std::round(trPos.GetY() + h * 0.5f);

		Renderer::RendererManager::Instance()->AdjustRectToCamera(&x, &y, &w, &h, scrollFactor);

		dstRect = { x, y, w, h };

		SDL_RenderCopyEx(renderer, texture->GetSDLTexture(), &srcRect, &dstRect, transform->GetWorldRotation(), nullptr, (SDL_RendererFlip) flipmode);
	}

	int Image::GetTextureWidth() const
	{
		return texture->GetWidth();
	}

	int Image::GetTextureHeight() const
	{
		return texture->GetHeight();
	}

	void Image::SetSrcRect(int x, int y, int w, int h) 
	{
		srcX = x; srcY = y;
		srcWidth = w; srcHeight = h;
	}

	Utilities::Vector2D Image::ScaledSize() 
	{
		auto scale = transform->GetLocalScale();
		return { texture->GetWidth() * scale.GetX(), texture->GetHeight() * scale.GetY() };
	}

	void Image::LoadTexture(CRefString texturePath)
	{
		fileName = texturePath;
		texture = Resources::ResourcesManager::Instance()->AddTexture(fileName);
		srcWidth = texture->GetWidth(); srcHeight = texture->GetHeight();
	}
}