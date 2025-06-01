#pragma once

#include "Component.h"
#include "Vector2D.h"

namespace Input {
	class InputManager;
}

namespace ECS {

	class Transform;
	class PhysicBody;

	class TopDownController : public Component {

	public:

		TopDownController() {};

		void Init() override;

		void Update(float dt) override;

		void FixedUpdate(float fixedDt) override;

		inline void SetBlockXAxis(bool block) { blockXAxis = block; }
		inline void SetBlockYAxis(bool block) { blockYAxis = block; }

		inline bool IsXAxisBlocked() { return blockXAxis; }
		inline bool IsYAxisBlocked() { return blockYAxis; }

		inline void SetVelocity(float vel) { velocity = vel; }
		inline float GetVelocity() { return velocity; }
		
		inline void ShouldClampDiagonalVelocity(bool clamp) { clampDiagonalVelocity = clamp; }
		inline bool IsDiagonalVelocityClamped() { return clampDiagonalVelocity; }

		inline void ShouldUsePhysics(bool usePhysics) { this->usePhysics = usePhysics; }
		inline bool IsUsingPhysics() { return usePhysics; }

	private:

		Input::InputManager* im{};

		Transform* transform{};
		PhysicBody* body{};

		Utilities::Vector2D direction{};

		bool blockXAxis{};
		bool blockYAxis{};
		float velocity{};
		bool clampDiagonalVelocity{};
		bool usePhysics{};

	};

}
