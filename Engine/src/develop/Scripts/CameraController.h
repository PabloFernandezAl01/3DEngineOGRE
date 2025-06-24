#pragma once

#include <Component.h>
#include "../ECSDefs.h"

class CameraController : public Component
{
public:

	void Start() override;

	void Update(float dt) override;

private:

	Transform* yawTr{};
	Transform* pitchTr{};

	float sensitivity{ 50 };
	float movementVel{ 500.f };

};

