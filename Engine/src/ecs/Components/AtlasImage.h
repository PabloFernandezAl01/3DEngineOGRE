#pragma once

#include "Component.h"
#include <SDL_rect.h>
#include "ETypes.h"
#include <vector>

using namespace std;

struct SDL_Renderer;

namespace Renderer {
	class Texture;
	class TargetTexture;
}

namespace ECS
{
	class Transform;

	struct SrcTrgRects
	{
		SrcTrgRects(int srcX, int srcY, int srcW, int srcH, int trgX, int trgY, int trgW, int trgH, int flip)
		{
			src.x = srcX;
			src.y = srcY;
			src.w = srcW;
			src.h = srcH;

			trg.x = trgX;
			trg.y = trgY;
			trg.w = trgW;
			trg.h = trgH;

			flipMode = flip;
		}

		SDL_Rect src{};
		SDL_Rect trg{};

		int flipMode;
	};

	struct Atlas
	{
		string fileName;
		vector<SrcTrgRects> rects;
		Renderer::Texture* texture{};
	};

	class AtlasImage : public Component
	{
	public:

		AtlasImage(vector<Atlas>& atlas, int width, int height);
		~AtlasImage();

		void Init() override;

		void Render() override;

		void SetScrollFactor(CRefVector2 scrollFactor) { this->scrollFactor = scrollFactor; }

		void BuildTexture();

	private:

		SDL_Rect srcRect{};
		SDL_Rect dstRect{};

		Transform* transform{};
		SDL_Renderer* renderer{};

		vector<Atlas> atlas;

		Renderer::TargetTexture* targetTexture{};

		int width{}, height{};

		Utilities::Vector2D scrollFactor{1, 1};

	};
}


