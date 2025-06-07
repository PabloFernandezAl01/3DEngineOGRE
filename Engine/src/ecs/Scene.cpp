#include "Scene.h"
#include "Entity.h"

#include "RendererManager.h"
#include <algorithm>

namespace ECS {

    Scene::Scene(CRefString name) : name(name) {}

    Scene::~Scene() 
    {
        for (auto& e : entities)
            delete e;

        entities.clear();
    }

    void Scene::Init() const
    {
        for (const auto& e : entities)
            e->Init();
    }

    void Scene::Start() const 
    {
        for (const auto& e : entities)
            e->Start();
    }

    void Scene::Update(float deltaTime) const
    {
        for (const auto& e : entities)
        {
            if (e->active && !e->removed)
                e->Udpate(deltaTime);
        }
    }

    void Scene::LateUpdate(float deltaTime) const
    {
        for (const auto& e : entities)
        {
            if (e->active && !e->removed)
                e->LateUpdate(deltaTime);
        }
    }

    void Scene::Render() const 
    {
		for (const auto& e : entities)
		{
			if (e->active && !e->removed)
				e->Render();
		}
    }

    void Scene::FixedUpdate(float fixedDeltaTime) const 
    {
        for (const auto& e : entities)
        {
            if (e->active && !e->removed)
                e->FixedUpdate(fixedDeltaTime);
        }
    }

    void Scene::HandleRemovedEntities() 
    {
        for (auto& it : removedEntities)
        {
            Entity* entity = *it; 
            entities.erase(it);
            delete entity;
        }

        removedEntities.clear();
    }

    void Scene::HandleInstantiatedEntities()
    {
        for (auto& e : instantiatedEntities)
        {
            e->Init();
            e->Start();
            entities.push_back(e);
        }

        instantiatedEntities.clear();
    }

    void Scene::OnDestroy() const 
    {
        for (const auto& e : entities)
            e->OnDestroy();
    }

    void Scene::OnDestroyRemovedEntities() const 
    {
        for (const auto& e : entities) 
        {
            if (e->removed)
                e->OnDestroy();
        }
    }

    void Scene::OnSceneUp() const 
    {
        for (const auto& e : entities)
            if (e->active && !e->removed)
                e->OnSceneUp();
    }

    void Scene::OnSceneDown() const 
    {
        for (const auto& e : entities)
            if (e->active && !e->removed)
                e->OnSceneDown();
    }

    Entity* Scene::CreateEntity(CRefString name)
    {
        Entity* e = new Entity(name);
        entities.push_back(e);
        return e;
    }

    Entity* Scene::CreateEntity(CRefString name, Entity* parent)
    {
        Entity* e = new Entity(name, parent);
        entities.push_back(e);
        return e;
    }

    void Scene::RemoveEntity(Entity* ent)
    {
        auto it = std::find(entities.begin(), entities.end(), ent);

        if (it != entities.end())
        {
            removedEntities.push_back(it);
            (*it)->removed = true;
        }
    }

    Entity* Scene::FindEntityByName(CRefString ent_name) 
    {
		auto it = std::find_if(entities.begin(), entities.end(), [&](const Entity* e) {
			   return e->name == ent_name;
		});

		return it != entities.end() ? *it : nullptr;
    }

}
