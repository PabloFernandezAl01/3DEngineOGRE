#pragma once

#include <Component.h>
#include "../ECSDefs.h"

class CameraController : public Component
{
public:

	void Init() override;

	void Update(float dt) override;

private:

	Transform* yawTr{};
	Transform* pitchTr{};

	float sensitivity{ 10 };
	float movementVel{ 400.f };

};

