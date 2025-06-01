#pragma once

#include "ETypes.h"

struct SDL_Renderer;

namespace Renderer
{
	class RendererManager;

	class DrawUtils
	{

	public:

		DrawUtils(RendererManager* renderer, SDL_Renderer* SDLRenderer);

		void DrawLine(int x1, int y1, int x2, int y2, int thickness, CRefColor color);
		void DrawSolidLine(int x1, int y1, int x2, int y2, int thickness, CRefColor color);

		void DrawCircle(int centerX, int centerY, int radius, CRefColor color);
		void DrawSolidCircle(int centerX, int centerY, int radius, CRefColor color);

	private:

		RendererManager* renderer;
		SDL_Renderer* SDLRenderer;
	};
}


