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

		Ogre::Entity* GetOgreEntity() { return mesh; }

		inline void SetMeshName(CRefString name) { meshName = name; }
		inline void SetMaterial(CRefString name) { materialName = name; }
		inline void SetCastShadows(bool cast) { castShadows = cast; }

	private:

		Ogre::Entity* mesh{};

		std::string meshName;
		std::string materialName;

		bool castShadows{};

	};
}



