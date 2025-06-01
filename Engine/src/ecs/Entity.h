#pragma once

#include <type_traits>
#include <ETypes.h>
#include <list>
#include <set>

using namespace std;

namespace ECS {

	class Component;
	class Scene;

	// This is a way to ensure that T is a Component
	template <typename T>
	concept IsComponent = is_base_of<Component, T>::value;

	class Entity {

		friend Scene;
		friend Component;

	public:

		struct EntityRenderOrderComparator {
			bool operator()(const Entity* a, const Entity* b) const {
				return a->renderOrder < b->renderOrder;
			}
		};

		Entity(CRefString ent_name, int renderOrder);

		Entity(CRefString ent_name, Scene* ent_scene);

		virtual ~Entity();

		virtual void Config();

		inline Scene* GetScene() const { return scene; }

		inline CRefString GetName() const { return name; }

		inline int GetRenderOrder() const { return renderOrder; }

		inline void SetLifeSpan(float lifeSpan) { this->lifeSpan = lifeSpan; lifeSpanActive = true; }

		// Sets the active flag of the entity
		void SetActive(bool ent_active);

		// Returns true if the entity is active on the scene, 0 otherwise
		inline bool IsActive() const { return active; }

		inline bool IsRemoved() const { return removed; }

		// Adds a T component to the entity
		template <typename T, typename ...Ts>
		requires IsComponent<T>
		T* AddComponent(Ts &&... args) 
		{
			T* c = new T(std::forward<Ts>(args)...);

			c->entity = this;
			components.push_back(c);

			return c;
		}

		// Returns true if the entity has the T component, false otherwise
		template <typename T>
		requires IsComponent<T>
		bool HasComponent() const
		{
			return GetComponent<T>() != nullptr;
		}

		// Returns a pointer to the T component if exists in the entity, nullptr otherwise
		template <typename T>
		requires IsComponent<T>
		T* GetComponent() const
		{
			for (const auto& c : components) 
			{
				T* v = dynamic_cast<T*>(c);
				if (v != nullptr)
					return v;
			}

			return nullptr;
		}

		inline const list<Component*> GetComponents() { return components; }

	private:

		void Init() const;

		void Start() const;

		void Udpate(float deltaTime);

		void LateUpdate(float deltaTime) const;

		void Render() const;

		// An update executed with the physics step rate
		void FixedUpdate(float fixedDeltaTime) const;

		// Called when the entity is set to active
		void OnActive() const;

		// Called when the entity is set to inactive
		void OnDeacitve() const;

		// Called when the scene is up
		void OnSceneUp() const;

		// Called when the scene is changed or destroyed
		void OnSceneDown() const;

		// Called when the entity starts colliding with other entity
		void OnCollisionEnter(Entity* b) const;

		// Called when the entity is colliding with other entity
		void OnCollisionStay(Entity* b) const;

		// Called when the entity exit the collider of the other entity
		void OnCollisionExit(Entity* b) const;

		// Called when the entity starts trigging an entity marked as trigger
		void OnTriggerEnter(Entity * b) const;

		// Called when the entity is trigging and entity marked as trigger
		void OnTriggerStay(Entity* b) const;

		// Called when the entity exits the trigger of the other entity marked as trigger
		void OnTriggerExit(Entity* b) const;

		// This lets you inspect a contact after the solver is finished. This is useful
		// for inspecting impulses.
		void OnPostSolve(Entity* b, float normalImpulse);

		// Called when the entity is removed
		void OnDestroy() const;

	private:

		// Name of the entity
		string name;

		// Flags to indicate if the entity is active or removed
		bool active{true}, removed{};

		int renderOrder{};

		// Lifespan
		bool lifeSpanActive{};
		float lifeSpan{};

		// Pointer to the scene where this entity is located
		Scene* scene{};

		// List of components associated with this entity
		list<Component*> components;
	};

}

