#pragma once

#include <Scene.h>

using namespace ECS;

class MainScene : public Scene
{
public:

	MainScene();

private:

	void CreateOgre();
	void CreateCamera();
	void CreateLight();

};