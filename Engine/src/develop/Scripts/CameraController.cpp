#include "CameraController.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Log.h"
#include "InputManager.h"
#include "RendererManager.h"

using namespace Input;

void CameraController::Init()
{
	Renderer::RendererManager::Instance()->SetAmbientLight({ 0.5f, 0.5f, 0.5f });
	Renderer::RendererManager::Instance()->SetDisplaySceneNodes(true);

	yawTr = entity->GetParent()->GetComponent<Transform>();
	pitchTr = entity->GetComponent<Transform>();
}

void CameraController::Update(float dt)
{
	auto& delta = InputManager::Instance()->GetMousePositionDelta();

	if (InputManager::Instance()->IsMouseButtonDown((int)InputManager::MOUSEBUTTON::RIGHT))
	{
		yawTr->Yaw(delta.GetX() * dt * sensitivity, Transform::TransformSpace::WORLD);
		pitchTr->Pitch(-delta.GetY() * dt * sensitivity, Transform::TransformSpace::LOCAL);
	}

	Vector3D direction{};

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_A))
		direction -= pitchTr->Right();

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_D))
		direction += pitchTr->Right();

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_E))
		direction += pitchTr->Up();

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_Q))
		direction -= pitchTr->Up();

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_W))
		direction += pitchTr->Forward();

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_S))
		direction -= pitchTr->Forward();

	yawTr->Translate(direction * dt * movementVel, Transform::TransformSpace::LOCAL);

}
