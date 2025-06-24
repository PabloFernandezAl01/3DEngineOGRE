#include "Animator.h"
#include "Entity.h"
#include "Components/Mesh.h"
#include "Log.h"
#include "OgreEntity.h"
#include "OgreAnimationState.h"
#include "OgreSkeletonInstance.h"

void ECS::Animator::Init()
{
	mesh = entity->GetComponent<Mesh>();

	if (!mesh)
	{
		Log::PrintError("Animator component", "To add an Animator component the entity must have a Mesh component");
		this->active = false;
	}

	// Configuration
	mesh->GetOgreEntity()->getSkeleton()->setBlendMode(Ogre::SkeletonAnimationBlendMode(blendMode));
}

void ECS::Animator::Update(float dt)
{
	for (auto& animation : states)
	{
		string animationName = animation.first;
		Ogre::AnimationState* animationState = animation.second;

		if (fadingIn[animationName])
		{
			float newWeight = states[animationName]->getWeight() + dt * fadeSpeed[animationName];

			states[animationName]->setWeight(clamp(newWeight, 0.f, 1.f));

			if (newWeight >= 1) fadingIn[animationName] = false;
		}

		if (fadingOut[animationName])
		{
			float newWeight = states[animationName]->getWeight() - dt * fadeSpeed[animationName];

			states[animationName]->setWeight(clamp(newWeight, 0.f, 1.f));

			if (newWeight <= 0)
			{
				animationState->setEnabled(false);
				fadingOut[animationName] = false;
			}
		}
	}
}

void ECS::Animator::SetAnimations(const vector<string>& animations)
{
	for (const auto& anim : animations)
	{
		Ogre::AnimationState* state =  mesh->GetOgreEntity()->getAnimationState(anim);
		states[anim] = mesh->GetOgreEntity()->getAnimationState(anim);
		states[anim]->setLoop(true);

		fadingIn[anim] = false;
		fadingOut[anim] = false;
	}
}

void ECS::Animator::SetAnimationEnabled(CRefString animation, bool enabled)
{
	if (!states.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	states[animation]->setEnabled(enabled);
}

void ECS::Animator::SetAnimationLoop(CRefString animation, bool loop)
{
	if (!states.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	states[animation]->setLoop(loop);
}

void ECS::Animator::SetAnimationLenght(CRefString animation, float lenght)
{
	if (!states.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	states[animation]->setLength(lenght);
}

void ECS::Animator::SetAnimationTimePosition(CRefString animation, float position)
{
	if (!states.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	states[animation]->setTimePosition(position);
}

void ECS::Animator::SetAnimationFadeSpeed(CRefString animation, float fadeSpeed)
{
	if (!states.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	this->fadeSpeed[animation] = fadeSpeed;
}
