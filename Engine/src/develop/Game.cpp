#include "Game.h"
#include "Scene.h"
#include "scenes/MainScene.h"
#include <string>

using namespace ECS;

Scene* Game::CreateScene()
{
	return new MainScene();
}