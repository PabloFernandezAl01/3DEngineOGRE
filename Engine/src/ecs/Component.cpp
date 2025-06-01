#include "Component.h"
#include "Entity.h"

namespace ECS {

	Scene* Component::GetScene() const
	{
		return entity->scene;
	}

	void Component::SetActive(bool active)
	{
		this->active = active;

		if (active)
			OnActive();
		else
			OnDeacitve();
	}
	void Component::SetLifeSpan(float lifespan)
	{
		entity->SetLifeSpan(lifespan);
	}
}
