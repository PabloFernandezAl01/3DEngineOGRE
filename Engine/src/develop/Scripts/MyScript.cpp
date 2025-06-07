#include "MyScript.h"
#include <Log.h>
#include "InputManager.h"
#include "RendererManager.h"
#include "Entity.h"
#include "Components/Transform.h"

void MyScript::Init()
{
	Renderer::RendererManager::Instance()->SetAmbientLight({ 0.5f, 0.5f, 0.5f });
	Renderer::RendererManager::Instance()->SetDisplaySceneNodes(true);

	tr = entity->GetComponent<Transform>();
}

void MyScript::Update(float dt)
{
	if (Input::InputManager::Instance()->IsKeyDown(SDL_SCANCODE_A))
	{
		tr->Translate({-vel * dt, 0, 0});
	}

	if (Input::InputManager::Instance()->IsKeyDown(SDL_SCANCODE_D))
	{
		tr->Translate({ vel * dt, 0, 0 });
	}

	if (Input::InputManager::Instance()->IsKeyDown(SDL_SCANCODE_W))
	{
		tr->Translate({ 0, 0, -vel * dt });
	}

	if (Input::InputManager::Instance()->IsKeyDown(SDL_SCANCODE_S))
	{
		tr->Translate({ 0, 0, vel * dt });
	}

	if (Input::InputManager::Instance()->IsKeyDown(SDL_SCANCODE_E))
	{
		tr->Translate({ 0, vel * dt, 0 });
	}

	if (Input::InputManager::Instance()->IsKeyDown(SDL_SCANCODE_Q))
	{
		tr->Translate({ 0, -vel * dt, 0 });
	}
}
