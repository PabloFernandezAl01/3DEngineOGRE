#pragma once

#include <ConfigManager.h>
#include <Singleton.h>

namespace Physics {

	class PhysicsManager : public Core::Singleton<PhysicsManager> {

		friend Singleton<PhysicsManager>;

	public:

		~PhysicsManager();

		void FixedUpdate(float fixedDeltaTime);

		void HandleBodies();

	private:
		
		PhysicsManager() {};

		PhysicsManager(const ConfigData& data);
	};
}
