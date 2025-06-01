#pragma once

#include "Component.h"
#include <SDL_rect.h>
#include "ETypes.h"

struct SDL_Renderer;

namespace Renderer {
	class Texture;
}

namespace ECS {

	class Transform;

	class Image : public Component {

		friend class Animation;

	public:

		Image(CRefString filename = "");

		~Image();

		void Init() override;

		void Render() override;

		int GetTextureWidth() const;

		int GetTextureHeight() const;

		void SetSrcRect(int x, int y, int w, int h);

		Utilities::Vector2D ScaledSize();

		void LoadTexture(CRefString texturePath);
		inline bool HasLoadedTexture() { return texture != nullptr; }
		inline Renderer::Texture* GetTexture() { return texture; }

		// Sets the flip mode for the image
		// 0 for no flip, 1 for flip horizontally
		// and 2 for flip vertically
		inline void SetFlipMode(int flipmode) { this->flipmode = flipmode; }

		void SetScrollFactor(CRefVector2 scrollFactor) { this->scrollFactor = scrollFactor; }

	private:

		SDL_Renderer* renderer{};
		Renderer::Texture* texture{};

		Transform* transform{};

		std::string fileName;
		int flipmode{};

		SDL_Rect srcRect{};
		SDL_Rect dstRect{};

		Utilities::Vector2D scrollFactor{1, 1};

		// Source Rect information
		int srcX{}, srcY{}, srcWidth{}, srcHeight{};

		SDL_Point* point{};
	};

}
