#pragma once

#include "Component.h"
#include "ETypes.h"

#include <SDL_render.h>
#include <vector>

struct SDL_Renderer;
typedef struct SDL_Vertex;

using namespace Utilities;
using namespace std;;

namespace Renderer {
	class Texture;
}

namespace ECS {

	class Transform;

	class CustomImage : public Component
	{
	public:

		CustomImage(CRefString fileName = "");

		~CustomImage() = default;

		void Init() override;

		void Render() override;

		int GetTextureWidth() const;

		int GetTextureHeight() const;

		void SetVertex(const vector<Vector2D>& uvs, const vector<int>& indices = {});

		void LoadTexture(CRefString texturePath);
		inline bool HasLoadedTexture() { return texture != nullptr; }
		inline void SetTexture(Renderer::Texture* texture) { this->texture = texture; }

		void SetScrollFactor(CRefVector2 scrollFactor) { this->scrollFactor = scrollFactor; }

	private:

		SDL_Renderer* renderer{};
		Renderer::Texture* texture{};

		Transform* transform{};

		string fileName;

		vector<SDL_Vertex> vertex;
		vector<int> indices;

		Utilities::Vector2D scrollFactor{ 1, 1 };

	};

}

