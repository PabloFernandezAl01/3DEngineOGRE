#pragma once

struct SDL_Texture;

namespace Renderer {

	class TargetTexture
	{
	public:

		TargetTexture(int width, int height);
		~TargetTexture();

		inline SDL_Texture* GetSDLTexture() { return texture; }

		inline int GetTextureWidth() { return width; }
		inline int GetTextureHeight() { return height; }

	private:

		int width{}, height{};

		SDL_Texture* texture{};
	};
}


