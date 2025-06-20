#include "Entity.h"
#include "Component.h"
#include "Scene.h"
#include "OgreSceneNode.h"
#include "SceneManager.h"
#include "RendererManager.h"

namespace ECS {

	Entity::Entity(CRefString ent_name) : name(ent_name)
	{
		sceneNode = Renderer::RendererManager::Instance()->CreateNodeFromRoot();
	}

	Entity::Entity(CRefString name, Entity* parent) : name(name), parent(parent) 
	{
		sceneNode = parent->GetSceneNode()->createChildSceneNode();
	}

	Entity::~Entity() 
	{
		for (auto& c : components)
			delete c;

		components.clear();
	}

	Scene* Entity::GetScene() const
	{
		return SceneManager::Instance()->GetCurrentScene();
	}

	void Entity::Init() const
	{
		for (const auto& c : components)
			c->Init();
	}

	void Entity::Start() const 
	{
		for (const auto& c : components)
			c->Start();
	}

	void Entity::Udpate(float deltaTime) 
	{
		for (const auto& c : components)
			if (c->IsActive())
				c->Update(deltaTime);

		// Lifespan
		if (lifeSpanActive)
		{
			lifeSpan -= deltaTime;

			if (lifeSpan <= 0)
				GetScene()->RemoveEntity(this);
		}
	}

	void Entity::LateUpdate(float deltaTime) const 
	{
		for (const auto& c : components)
			if (c->IsActive())
				c->LateUpdate(deltaTime);
	}

	void Entity::Render() const 
	{
		for (const auto& c : components)
			if (c->IsActive()) c->Render();
	}

	void Entity::FixedUpdate(float fixedDeltaTime) const 
	{
		for (const auto& c : components)
			if (c->IsActive())
				c->FixedUpdate(fixedDeltaTime);
	}

	void Entity::OnActive() const {
		for (const auto& c : components)
			c->OnActive();
	}

	void Entity::OnDeacitve() const
	{
		for (const auto& c : components)
			c->OnDeacitve();
	}

	void Entity::OnSceneUp() const 
	{
		for (const auto& c : components)
			if (c->IsActive()) 
				c->OnSceneUp();
	}

	void Entity::OnSceneDown() const 
	{
		for (const auto& c : components)
			if (c->IsActive()) 
				c->OnSceneDown();
	}

	void Entity::OnCollisionEnter(Entity* b) const 
	{
		for (const auto& c : components)
			if (c->IsActive()) 
				c->OnCollisionEnter(b);
	}

	void Entity::OnCollisionStay(Entity* b) const 
	{
		for (const auto& c : components)
			if (c->IsActive()) 
				c->OnCollisionStay(b);
	}

	void Entity::OnCollisionExit(Entity* b) const
	{
		for (const auto& c : components)
			if (c->IsActive()) 
				c->OnCollisionExit(b);
	}

	void Entity::OnTriggerEnter(Entity* b) const 
	{
		for (const auto& c : components)
			if (c->IsActive()) 
				c->OnTriggerEnter(b);
	}

	void Entity::OnTriggerStay(Entity* b) const 
	{
		for (const auto& c : components)
			if (c->IsActive()) 
				c->OnTriggerStay(b);
	}

	void Entity::OnTriggerExit(Entity* b) const 
	{
		for (const auto& c : components)
			if (c->IsActive()) 
				c->OnTriggerExit(b);
	}

	void Entity::OnPostSolve(Entity* b, float normalImpulse)
	{
		for (const auto& c : components)
			if (c->IsActive())
				c->OnPostSolve(b, normalImpulse);
	}

	void Entity::OnDestroy() const
	{
		for (const auto& c : components)
			c->OnDestroy();
	}

	void Entity::SetParent(Entity* e)
	{
		parent->GetSceneNode()->removeChild(sceneNode);
		e->GetSceneNode()->addChild(sceneNode);
	}

	Entity* Entity::GetParent() const
	{
		return parent;
	}

	void Entity::SetActive(bool ent_active) {
		active = ent_active;

		if (active) 
			OnActive();
		else 
			OnDeacitve();
	}
}
