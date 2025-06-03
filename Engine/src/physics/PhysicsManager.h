#pragma once

#include <ConfigManager.h>
#include <ESingleton.h>

namespace Physics {

	class PhysicsManager : public Core::ESingleton<PhysicsManager> {

		friend ESingleton<PhysicsManager>;

	public:

		~PhysicsManager();

		void FixedUpdate(float fixedDeltaTime);

	private:
		
		PhysicsManager() {};

		PhysicsManager(const ConfigData& data);
	};
}
