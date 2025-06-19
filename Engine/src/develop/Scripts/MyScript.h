#pragma once

#include <Component.h>
#include "../ECSDefs.h"
#include "ETypes.h"

class MyScript : public Component
{
public:

	void Init() override;

	void Update(float dt) override;

private:

	Transform* tr{};
	Transform* parentTr{};

	Vector3D originalPosition;

	float angularvel{ 200.f };
	float moveVel{ 200 };
	float rotDir{ 1 };
	float moveDir{ 1 };
	float scaleVel{ 100 };

};

