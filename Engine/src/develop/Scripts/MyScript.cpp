#include "MyScript.h"
#include <Log.h>
#include "InputManager.h"
#include "RendererManager.h"
#include "Entity.h"
#include "Components/Transform.h"

using namespace Input;

void MyScript::Init()
{
	tr = entity->GetComponent<Transform>();
	parentTr = entity->GetParent()->GetComponent<Transform>();

	originalPosition = tr->GetPosition();
}

void MyScript::Update(float dt)
{
	// Rotate parent
	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::U))
	{
		parentTr->Rotate({ angularvel * dt * rotDir, 0, 0 }, Transform::TransformSpace::LOCAL);
	}

	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::I))
	{
		parentTr->Rotate({ 0, angularvel * dt * rotDir, 0 }, Transform::TransformSpace::LOCAL);
	}

	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::O))
	{
		parentTr->Rotate({ 0, 0, angularvel * dt * rotDir }, Transform::TransformSpace::LOCAL);
	}

	if (InputManager::Instance()->IsLetterPressed(InputManager::KB_LETTERS::P))
	{
		rotDir *= -1;
	}

	if (InputManager::Instance()->IsLetterPressed(InputManager::KB_LETTERS::R))
	{
		parentTr->SetOrientation(Quaternion::FromEulerAngles({ 0,0,0 }));
		parentTr->SetPosition({0,0,0});
		tr->SetOrientation(Quaternion::FromEulerAngles({ 0,0,0 }));
		tr->SetPosition(originalPosition);
	}

	// Move child
	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::T))
	{
		tr->Scale(Vector3D::Forward() * scaleVel * dt, Transform::TransformSpace::WORLD);
	}

	if (InputManager::Instance()->IsLetterDown(InputManager::KB_LETTERS::G))
	{
		tr->Scale(Vector3D::Forward() * -scaleVel * dt, Transform::TransformSpace::WORLD);
	}
}
