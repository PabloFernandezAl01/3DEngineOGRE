#pragma once

#include "Component.h"
#include "ETypes.h"

namespace Ogre
{
	class Light;
}

namespace ECS
{
	class Light : public Component
	{
	public:

		enum class LightType { POINT = 0, DIRECTIONAL = 1, SPOTLIGHT = 2, RECTLIGHT = 3 };

		void Init() override;

		inline void SetType(const LightType& type) { lightType = type; }

		void SetDiffuse(CRefColor color) { diffuse = color; }

		void SetSpecular(CRefColor color) { specular = color; }

		void SetAttenuation(float range, float constant, float linear, float quadratic) 
		{ this->range = range; this->constant = constant; this->linear = linear; this->quadratic = quadratic; }

	private:

		Ogre::Light* light{};

		// Configuration
		LightType lightType{};
		Core::Color diffuse;
		Core::Color specular;

		// Attenuation
		float range, constant, linear, quadratic;
	};
}

