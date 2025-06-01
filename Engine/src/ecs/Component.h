#pragma once

namespace ECS {

	class Entity;
	class Scene;

	class Component {

		friend Entity;

	public:

		Component() = default;
		virtual ~Component() = default;

		inline Entity* GetEntity() const { return entity; }

		Scene* GetScene() const;

		inline bool IsActive() const { return active; }

		void SetActive(bool active);

		void SetLifeSpan(float lifespan);

		virtual void Config() {};

		virtual void OnActive() {};

		virtual void OnDeacitve() {};

		virtual void OnSceneUp() {};

		virtual void OnSceneDown() {};

		virtual void OnCollisionEnter(Entity* b) {};

		virtual void OnCollisionStay(Entity* b) {};

		virtual void OnCollisionExit(Entity* b) {};

		virtual void OnTriggerEnter(Entity* b) {};

		virtual void OnTriggerStay(Entity* b) {};

		virtual void OnTriggerExit(Entity* b) {};

		virtual void OnPostSolve(Entity* b, float normalImpulse) {};

		virtual void OnDestroy() {};

	private:

		virtual void Init() {};

		virtual void Start() {};

		virtual void Update(float deltaTime) {};

		virtual void LateUpdate(float deltaTime) {};

		virtual void Render() {};

		virtual void FixedUpdate(float fixedDeltaTime) {};

	protected:

		Entity* entity{};

		bool active{true};
	};
}

