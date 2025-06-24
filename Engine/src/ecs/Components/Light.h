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

		void SetSpotLightFallOff(float fallOff) { spotLightFallOff = fallOff; }

		void SetSpotLightInnerAngle(float angle) { spotLightInnerAngle = angle; }

		void SetSpotLightOuterAngle(float angle) { spotLightOuterAngle = angle; }

	private:

		Ogre::Light* light{};

		// Configuration
		LightType lightType{ LightType::DIRECTIONAL };
		Core::Color diffuse{ 1.0f, 1.0f, 1.0f};
		Core::Color specular{ 1.0f, 1.0f, 1.0f };

		// Attenuation
		float range{ 100000 }, constant{ 1.0 }, linear{}, quadratic{};

		float spotLightFallOff{};
		float spotLightInnerAngle{};
		float spotLightOuterAngle{};
	};
}

