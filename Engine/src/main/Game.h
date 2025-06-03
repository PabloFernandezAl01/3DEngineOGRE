#pragma once

#include <Component.h>

namespace ECS
{
	class Scene;
	class Transform;
}

using namespace ECS;

class Game
{
public:

	Game() = default;

	Scene* CreateGameScene();
};

class MyScript : public Component
{
public:

	void Init() override;

	void Update(float dt) override;

private:

	Transform* tr;

};

