#pragma once

#include <Entity.h>
#include <ETypes.h>
#include <list>
#include <set>

using namespace std;

class Engine;

namespace ECS {

	class SceneManager;

	// This is a way to ensure that T is an Entity
	template <typename T>
	concept IsEntity = is_base_of<Entity, T>::value;

	class Scene {

		friend SceneManager;
		friend Engine;

	public:
		Scene(CRefString sce_name = "New Scene");

		~Scene();

		// Returns the name of the scene
		inline CRefString GetName() { return name; }

		// Sets the name of the scene
		inline void SetName(CRefString sce_name) { name = sce_name; }

		// Creates an entity on the scene and returns the pointer
		Entity* CreateEntity(CRefString name, int renderOrder = 0);

		// Adds a T entity to the scene
		template <typename T, typename ...Ts>
		requires IsEntity<T>
		T* AddEntity(Ts &&... args) {

			T* e = new T(std::forward<Ts>(args)...);

			e->scene = this;
			entities.emplace(e);

			return e;
		}

		template <typename T, typename ...Ts>
		requires IsEntity<T>
		T* Instantiate(Ts &&... args)
		{
			T* e = new T(std::forward<Ts>(args)...);
			e->scene = this;
			instantiatedEntities.push_back(e);

			return e;
		}

		void RemoveEntity(Entity* ent);

		// Returns the pointer to an entity that matches with the name,
		// nullptr otherwise (Not an efficient way to find an entity)
		Entity* FindEntityByName(CRefString ent_name);

	private:

		void Start() const;

		void Init() const;

		void Update(float deltaTime) const;

		void LateUpdate(float deltaTime) const;

		void Render() const;

		void FixedUpdate(float fixedDeltaTime) const;

		void HandleRemovedEntities();

		void HandleInstantiatedEntities();

		void OnDestroy() const;

		void OnDestroyRemovedEntities() const;

		// Called when the scene is up
		void OnSceneUp() const;

		// Called when the scene is changed or destroyed
		void OnSceneDown() const;

	private:

		string name;

		list<Entity*> entities;
		list<list<Entity*>::iterator> removedEntities;
		list<Entity*> instantiatedEntities;
	};
}

