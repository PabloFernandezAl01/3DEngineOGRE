#pragma once
#include "Component.h"
#include <ETypes.h>

namespace Ogre
{
	class Entity;
}

namespace ECS
{
	class PlaneMesh : public Component
	{
	public:

		void Init() override;

		inline void SetName(CRefString name) { this->name = name; }

		inline void SetNormal(CRefVector3D normal) { this->normal = normal; }

		inline void SetDistanceFromOrigin(CRefVector3D distance) { distanceFromOrigin = distance; }

		inline void SetSize(CRefVector2D size) { this->size = size; }

		inline void SetSegments(CRefVector2D segments) { this->segments = segments; }

		inline void SetNumTexCoordSets(int num) { numTexCoordSets = num; }

		inline void SetUTile(int n) { uTile = n; };

		inline void SetVTile(int n) { vTile = n; };

		inline void SetUpVector(CRefVector3D v) { upVector = v; }

		inline void SetMaterial(CRefString name) { materialName = name; }

		inline void SetCastShadows(bool cast) { castShadows = cast; }

	private:

		std::string name;

		Vector3D normal;

		Vector3D distanceFromOrigin{};

		Vector2D size;

		Vector2D segments;

		int numTexCoordSets{ 1 };

		float uTile{ 1 }, vTile{ 1 };

		Vector3D upVector;

		Ogre::Entity* mesh{};

		std::string materialName;

		bool castShadows{};
	};
}



