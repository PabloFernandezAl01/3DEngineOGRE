#pragma once
#include <Component.h>
#include "../ECSDefs.h"

class CharacterController : public Component
{
public:

	void Start() override;

private:

	Transform* transform;
	Animator* animator;

};

