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

		void SetMeshName(CRefString name) { meshName = name; }

	private:

		Ogre::Entity* mesh = nullptr;
		std::string meshName;

	};
}



