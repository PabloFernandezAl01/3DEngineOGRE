#pragma once

#include <Scene.h>

using namespace ECS;

class MainScene : public Scene
{
public:

	MainScene();

private:

	void CreateObjects();
	void CreateCamera();
	void CreateLight();

};