#pragma once

#include <Component.h>
#include "../ECSDefs.h"

class MyScript : public Component
{
public:

	void Init() override;

	void Update(float dt) override;

private:

	Transform* tr{};

	float vel{ 500.f };

};

