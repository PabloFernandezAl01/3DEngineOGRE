#include "CharacterController.h"
#include "Entity.h"
#include "Components/Animator.h"
#include "Components/Transform.h"
#include "vector"

void CharacterController::Start()
{
	transform = entity->GetComponent<Transform>();
	animator = entity->GetComponent<Animator>();

	std::vector<std::string> animsNames{ "IdleBase", "IdleTop", "RunBase", "RunTop", "HandsClosed", "HandsRelaxed", "DrawSwords",
	"SliceVertical", "SliceHorizontal", "Dance", "JumpStart", "JumpLoop", "JumpEnd" };

	animator->SetAnimations(animsNames);

 	animator->SetAnimationEnabled("Dance", true);
}
