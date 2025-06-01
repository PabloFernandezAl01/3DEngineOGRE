#pragma once

#include "Component.h"
#include "ETypes.h"
#include <string>

namespace Input {
	class InputManager;
}

namespace ECS {

	class Transform;
	class PhysicBody;
	class Entity;

	class PlatformController : public Component {

	public:

		PlatformController() = default;

		inline void SetVelocity(float vel) { velocity = vel; }

		inline void SetMaxVelocity(float maxVel) { maxVelocity = maxVel; }

		inline void SetJumpForce(float force) { jumpForce = force; }

		inline void SetAvailableJumps(int jumps) { avalaibleJumps = jumps; }

		inline void SetPlatformLayer(CRefString layer) { platformLayer = layer; }

		// Must be between 0 and 1
		inline void SetHorizontalDamping(float damping) { horizontalDamping = damping; }

	private:

		void Init() override;

		void Update(float dt) override;

		void FixedUpdate(float fixedDt) override;

		void OnCollisionEnter(Entity* ent) override;

		void OnCollisionExit(Entity* ent) override;

	private:

		Input::InputManager* im{};

		Transform* transform{};
		PhysicBody* body{};

		float direction{};

		float velocity{};
		float maxVelocity{ 5.f };
		float jumpForce{ 1.f };
		std::string platformLayer{};
		float horizontalDamping{};
		int avalaibleJumps{1};

		int nJumps{};

		bool onGround{};
		bool hasJumped{};
	};

}

