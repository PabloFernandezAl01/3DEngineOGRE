#pragma once

#include "Component.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "ETypes.h"

namespace Ogre
{
	class Entity;
	class AnimationState;
}

using namespace std;

namespace ECS
{
	class Mesh;

	class Animator : public Component
	{
	public:

		struct AnimData
		{
			Ogre::AnimationState* state{ nullptr };
			bool looping{ true };
			bool fadingIn;
			bool fadingOut;
			float fadeInSpeed{ 1.f };
			float fadeOutSpeed{ 1.f };
			float speed{ 1.f };
		};

		enum class BlendMode {AVERAGE, CUMULATIVE};

		void Init() override;

		void Update(float dt) override;

		vector<string> GetAnimationsNames();

		// Use this method to initialise animations
		void SetAnimations(const vector<string>& animationsNames);

		void SetBlendMode(const BlendMode& blendMode);

		void SetAnimationEnabled(CRefString animation, bool enabled);

		void SetAnimationLoop(CRefString animation, bool loop);

		void SetAnimationLenght(CRefString animation, float lenght);

		void SetAnimationTimePosition(CRefString animation, float position);

		void SetAnimationFadeInSpeed(CRefString animation, float fadeInSpeed);

		void SetAnimationFadeOutSpeed(CRefString animation, float fadeOutSpeed);

	private:

		Mesh* mesh;
		unordered_map<string, AnimData> animations;

	};
}



