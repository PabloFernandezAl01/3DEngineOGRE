#pragma once

#include <ETypes.h>

typedef struct _TTF_Font TTF_Font;
namespace Renderer {

	class Texture;
	class Font {

	public:

		Font(CRefString filepath, int pointSize);

		~Font();

		inline TTF_Font* GetSDLFont() { return font; }
		Texture* CreateText(std::string const& message);
		Texture* CreateWrappedText(std::string const& message, int maxSize);

	private:

		int pointSize{};
		std::string path{};

		TTF_Font* font{};
	};

}