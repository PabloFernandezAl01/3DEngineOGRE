#pragma once

#include <Component.h>

using namespace ECS;

class MyScript : public Component
{
public:

	void Init() override;

	void Update(float dt) override;

private:

};

