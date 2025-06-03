#pragma once

namespace Physics 
{
	class PhysicsManager;
}

namespace Renderer 
{
	class RendererManager;
}

namespace Input 
{
	class InputManager;
}

namespace ECS 
{
	class SceneManager;
}

namespace Core 
{
	class ETime;
}

class Engine {

public:

	Engine();

	bool Init();
	void Update();
	void Close();

private:

	Renderer::RendererManager* rendererManager{};
	Physics::PhysicsManager* physicsManager{};
	Input::InputManager* inputManager{};
	ECS::SceneManager* sceneManager{};
	Core::ETime* engineTime{};

};

