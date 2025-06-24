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

		enum class BlendMode {AVERAGE, CUMULATIVE};

		void Init() override;

		void Update(float dt) override;

		void SetAnimations(const vector<string>& animations);

		inline void SetBlendMode(const BlendMode& blendMode) { this->blendMode = blendMode; };

		void SetAnimationEnabled(CRefString animation, bool enabled);

		void SetAnimationLoop(CRefString animation, bool loop);

		void SetAnimationLenght(CRefString animation, float lenght);

		void SetAnimationTimePosition(CRefString animation, float position);

		void SetAnimationFadeSpeed(CRefString animation, float fadeSpeed);

	private:

		Mesh* mesh;

		unordered_map<string, Ogre::AnimationState*> states;
		unordered_map<string, bool> fadingIn;
		unordered_map<string, bool> fadingOut;
		unordered_map<string, float> fadeSpeed;

		BlendMode blendMode{};

	};
}



