#pragma once

namespace Physics {
	class PhysicsManager;
}

namespace Renderer {
	class RendererManager;
}

namespace Input {
	class InputManager;
}

namespace ECS {
	class RenderManager;
	class SceneManager;
	class PrefabManager;
}

namespace Resources {
	class ResourcesManager;
}

namespace Utilities {
	class ETime;
}

class Engine {

public:

	Engine();

	bool Init();
	void Update();
	void Close();

private:

	Resources::ResourcesManager* resourcesManager{};
	Renderer::RendererManager* rendererManager{};
	Physics::PhysicsManager* physicsManager{};
	Input::InputManager* inputManager{};
	ECS::RenderManager* renderManager{};
	ECS::SceneManager* sceneManager{};
	Utilities::ETime* engineTime{};

};

