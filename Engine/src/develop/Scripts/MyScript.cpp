#include "MyScript.h"
#include <Log.h>
#include "InputManager.h"
#include "RendererManager.h"

void MyScript::Init()
{
	Renderer::RendererManager::Instance()->SetAmbientLight({ 0.5f, 0.5f, 0.5f });
	Renderer::RendererManager::Instance()->SetDisplaySceneNodes(true);
}

void MyScript::Update(float dt)
{
	if (Input::InputManager::Instance()->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		Log::Print("", "Space!");
	}
}
