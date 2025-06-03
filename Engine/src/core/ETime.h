#pragma once

#include "ESingleton.h"
#include <string>

namespace Core {

	class ETime : public ESingleton<ETime> {

		friend ESingleton<ETime>;

	public:

		float GetTimeSinceBegining();
		float GetTimeSinceBeginingMilliseconds();
		float GetDeltaTime();
		float GetFrameRate();
		float GetPhysicsDeltaTime();
		static std::string Time2String(float time);

		float deltaTime;
		float fixedDeltaTime;
		float timeSinceStart;
		unsigned long long frames;

	private:

		ETime();

		float CalculateFrameRate();

	};
}