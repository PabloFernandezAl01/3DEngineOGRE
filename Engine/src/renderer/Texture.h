#pragma once

#include <ETypes.h>

struct SDL_Texture;

namespace Renderer {
	
	class Texture {

	public:

		Texture(CRefString filepath);
		Texture(SDL_Texture* text);

		~Texture();

		inline SDL_Texture* GetSDLTexture() { return texture; }

		inline int GetWidth() { return width; }
		inline int GetHeight() { return height; }

	private:

		SDL_Texture* texture{};

		int width{}, height{};

	};

}