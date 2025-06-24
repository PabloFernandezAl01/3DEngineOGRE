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
}

void ECS::Animator::Update(float dt)
{
	for (auto& animation : animations)
	{
		AnimData& animData = animation.second;

		if (animData.state->getEnabled())
		{
			// Update de animaciones
			animData.state->addTime(dt * animData.speed);
		}

		if (animData.fadingIn)
		{
			float newWeight = animData.state->getWeight() + dt * animData.fadeInSpeed;
			animData.state->setWeight(clamp(newWeight, 0.f, 1.f));

			if (newWeight >= 1) animData.fadingIn = false;
		}
		
		if (animData.fadingOut)
		{
			float newWeight = animData.state->getWeight() + dt * animData.fadeOutSpeed;
			animData.state->setWeight(clamp(newWeight, 0.f, 1.f));

			if (newWeight <= 0)
			{
				animData.state->setEnabled(false);
				animData.fadingOut = false;
			}
		}
	}
}

vector<string> ECS::Animator::GetAnimationsNames()
{
	vector<string> names;
	Ogre::AnimationStateSet* animsSet = mesh->GetOgreEntity()->getAllAnimationStates();

	if (animsSet)
	{
		Ogre::AnimationStateIterator it = animsSet->getAnimationStateIterator();
		while (it.hasMoreElements())
		{
			Ogre::AnimationState* animState = it.getNext();
			names.push_back(animState->getAnimationName());
		}
	}

	return names;
}


void ECS::Animator::SetAnimations(const vector<string>& animationsNames)
{
	for (const auto& animName : animationsNames)
	{
		Ogre::AnimationState* state =  mesh->GetOgreEntity()->getAnimationState(animName);
		animations[animName] = AnimData();
		animations[animName].state = state;
	}
}

void ECS::Animator::SetBlendMode(const BlendMode& blendMode)
{
	mesh->GetOgreEntity()->getSkeleton()->setBlendMode(Ogre::SkeletonAnimationBlendMode(blendMode));
}

void ECS::Animator::SetAnimationEnabled(CRefString animation, bool enabled)
{
	if (!animations.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	animations[animation].state->setEnabled(enabled);
}

void ECS::Animator::SetAnimationLoop(CRefString animation, bool loop)
{
	if (!animations.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	animations[animation].state->setLoop(loop);
}

void ECS::Animator::SetAnimationLenght(CRefString animation, float lenght)
{
	if (!animations.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	animations[animation].state->setLength(lenght);
}

void ECS::Animator::SetAnimationTimePosition(CRefString animation, float position)
{
	if (!animations.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	animations[animation].state->setTimePosition(position);
}

void ECS::Animator::SetAnimationFadeInSpeed(CRefString animation, float fadeInSpeed)
{
	if (!animations.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	animations[animation].fadeInSpeed = fadeInSpeed;
}

void ECS::Animator::SetAnimationFadeOutSpeed(CRefString animation, float fadeOutSpeed)
{
	if (!animations.contains(animation))
	{
		Log::PrintError("Animator component", "Animation with name " + animation + " does not exist!");
		return;
	}

	animations[animation].fadeInSpeed = fadeOutSpeed;
}
