#pragma once
#include "Component.h"
#include <ETypes.h>

namespace Ogre
{
	class Entity;
}

namespace ECS
{
	class Mesh : public Component
	{
	public:

		void Init() override;

		inline void SetMeshName(CRefString name) { meshName = name; }
		inline void SetMaterial(CRefString name) { materialName = name; }

	private:

		Ogre::Entity* mesh{};

		std::string meshName;
		std::string materialName;

	};
}



