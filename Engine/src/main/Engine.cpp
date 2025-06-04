#include "Engine.h"

#include <ConfigManager.h>
#include <RendererManager.h>
#include <PhysicsManager.h>
#include <SoundManager.h>
#include <InputManager.h>
#include <SceneManager.h>
#include <Component.h>
#include <Scene.h>
#include <ETime.h>
#include <chrono>
#include <Log.h>

#include "Game.h"

using namespace std::chrono;

Engine::Engine() {}

bool Engine::Init() 
{
	// --------------------------------- MANAGERS -----------------------------------

	if (!ConfigManager::Init("config")->Valid())
	{
		Log::PrintError("CRITICAL ERROR", "The engine couldn't load the configuration file <config.json>");
		return false;
	}

	sceneManager = ECS::SceneManager::Init();
	if (!sceneManager->Valid()) return false;

	rendererManager = Renderer::RendererManager::Init(ConfigManager::Instance()->GetData());
	if (!rendererManager->Valid()) return false;

	physicsManager = Physics::PhysicsManager::Init(ConfigManager::Instance()->GetData());
	if (!physicsManager->Valid()) return false;

	inputManager = Input::InputManager::Init(ConfigManager::Instance()->GetData());
	if (!inputManager->Valid()) return false;

	if (!Sound::SoundManager::Init(ConfigManager::Instance()->GetData())->Valid()) return false;

	engineTime = Core::ETime::Init();

	
	// Game Scene
	Game g;
	auto* scene = g.CreateScene();
	scene->Init();

	sceneManager->ChangeScene(scene, SceneManager::LOAD_MODE::PUSH);
	sceneManager->ManageScenes();

	return true;
}

void Engine::Update() 
{
	SDL_Event event;

	steady_clock::time_point beginTime = high_resolution_clock::now();
	steady_clock::time_point physicsTime = beginTime;
	steady_clock::time_point startTime = beginTime;

	while (true) 
	{
		// Scene
		auto scene = sceneManager->GetCurrentScene();

		if (scene == nullptr) break;

		// Input
		if (!inputManager->HandleInput(event)) break;

		// FixedUpdate
		while (physicsTime < beginTime) 
		{
			scene->FixedUpdate(engineTime->fixedDeltaTime);
			physicsManager->FixedUpdate(engineTime->fixedDeltaTime);

			physicsTime += std::chrono::milliseconds((int)(engineTime->fixedDeltaTime * 1000));
		}

		// Update
		scene->Update(engineTime->deltaTime);

		// LateUpdate
		scene->LateUpdate(engineTime->deltaTime);

		// Render
		rendererManager->PresentRenderer();

		// OnDestroy
		scene->OnDestroyRemovedEntities();

		// Remove dead entities and components
		scene->HandleRemovedEntities();

		// Init instantiated entities and add them to the scene
		scene->HandleInstantiatedEntities();

		// Change scene if necessary
		sceneManager->ManageScenes();

		// Time
		steady_clock::time_point endTime = high_resolution_clock::now();

		duration<float, std::milli> timeSinceStart = endTime - startTime;
		duration<double, std::milli> frameTime = endTime - beginTime;

		engineTime->timeSinceStart = timeSinceStart.count();
		engineTime->deltaTime = frameTime.count() * 0.001f;
		engineTime->frames++;

		beginTime = endTime;
	}
}

void Engine::Close() 
{
	inputManager->Close();
	rendererManager->Close();
	sceneManager->Close();
	physicsManager->Close();
}
