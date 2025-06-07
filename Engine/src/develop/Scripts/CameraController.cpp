#include "CameraController.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Log.h"
#include "InputManager.h"

using namespace Input;

void CameraController::Init()
{
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
		direction += {-1, 0, 0};

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_D))
		direction += {1, 0, 0};

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_E))
		direction += {0, 1, 0};

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_Q))
		direction += {0, -1, 0};

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_W))
		direction += {0, 0, -1};

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_S))
		direction += {0, 0, 1};

	yawTr->Translate(direction * dt * movementVel);
}
