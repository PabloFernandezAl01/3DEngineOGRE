#pragma once

#include "Entity.h"
#include <vector>

using namespace Utilities;

namespace Renderer {
	class Texture;
}

namespace ECS
{
	class Transform;
	class CustomImage;
	class CustomBody;

	class Entity;

	class BreakSlice : public Entity
	{
	public:

		BreakSlice(CRefString name, int renderOrder);

		void Config() override;

		inline void SetVertex(const std::vector<Vector2D>& vertex) { this->vertex = vertex; }
		inline void SetOriginalRectangle(CRefVector2 lu, CRefVector2 size) { rectLU = lu; rectSize = size; }
		inline void SetOriginalTexture(Renderer::Texture* texture) { this->texture = texture; }
		inline void SetOriginalPosition(CRefVector2 pos) { originalPos = pos; };
		inline void SetOriginalScale(CRefVector2 scale) { originalScale = scale; }
		inline void SetOriginalRotation(float rotation) { originalRotation = rotation; }
		inline void SetPhysicsLayer(CRefString layer) { layerName = layer; }

	private:

		Transform* tr{};
		CustomImage* img{};
		CustomBody* customBody{};

		Vector2D rectLU;
		Vector2D rectSize;

		Vector2D originalPos;
		Vector2D originalScale;
		float originalRotation{};

		std::string layerName;

		Renderer::Texture* texture{};

		std::vector<Vector2D> vertex;
	};
}
