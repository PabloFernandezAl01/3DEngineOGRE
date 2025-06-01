#include "TargetTexture.h"
#include "RendererManager.h"
#include <SDL_image.h>

Renderer::TargetTexture::TargetTexture(int width, int height) : width(width), height(height)
{
	texture = SDL_CreateTexture(Renderer::RendererManager::Instance()->GetRenderer(),
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width,
		height);
}

Renderer::TargetTexture::~TargetTexture()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}
