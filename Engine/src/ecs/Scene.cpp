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

    void Scene::Init()  const
    {
        // In an ECS design the S stands for System. In a game engine a system could be
        // the physics system, audio system, IO system... etc. Same as components, entities
        // and scenes, systems should also have their init, update... callbacks so
        // for example the IO system can clean the data or whatever need that could come up

        // So in this case these two lines of code that reset camera position and scale should
        // go into Init() callback in Renderer Manager (Renderer System). As this is not frequent
        // I'll leave this here until I implement a decent System Manager
        /*Renderer::RendererManager::Instance()->SetCameraPosition(cameraPosition);
        Renderer::RendererManager::Instance()->SetCameraScale(cameraScale);*/

        for (const auto& e : entities)
            e->Init();
    }

    void Scene::Start() const 
    {
        for (const auto& e : entities)
            e->Start();
    }

    void Scene::Config()
	{
		for (const auto& e : entities)
			e->Config();
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
            e->Config();
            entities.emplace(e);
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

    Entity* Scene::CreateEntity(CRefString name, int renderOrder)
    {
        Entity* e = new Entity(name, this);

        e->renderOrder = renderOrder;
        e->scene = this;

        entities.emplace(e);

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
