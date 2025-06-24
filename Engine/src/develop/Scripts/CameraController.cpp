#include "CameraController.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Log.h"
#include "InputManager.h"
#include "RendererManager.h"

using namespace Input;

void CameraController::Start()
{
	yawTr = entity->GetParent()->GetComponent<Transform>();
	pitchTr = entity->GetComponent<Transform>();

	pitchTr->LookAt({ 0, 200, 0 });
}

void CameraController::Update(float dt)
{
	auto& delta = InputManager::Instance()->GetMousePositionDelta();

	if (InputManager::Instance()->IsMouseButtonDown(InputManager::MOUSEBUTTON::RIGHT))
	{
		yawTr->Yaw(delta.GetX() * dt * sensitivity, Transform::TransformSpace::WORLD);
		pitchTr->Pitch(-delta.GetY() * dt * sensitivity, Transform::TransformSpace::LOCAL);
	}

	Vector3D direction{};

	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::A))
		direction -= pitchTr->Right();

	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::D))
		direction += pitchTr->Right();

	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::E))
		direction += pitchTr->Up();

	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::Q))
		direction -= pitchTr->Up();

	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::W))
		direction += pitchTr->Forward();

	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::S))
		direction -= pitchTr->Forward();

	if (InputManager::Instance()->IsLetterPressed(InputManager::KB_LETTERS::R))
		yawTr->SetPosition({0, 200, 200});

	yawTr->Translate(direction.Normalize() * dt * movementVel, Transform::TransformSpace::LOCAL);

}
