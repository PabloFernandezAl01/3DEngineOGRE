#include "ETime.h"
#include <sstream>
#include <iomanip>

namespace Utilities {

	ETime::ETime() {
		deltaTime = 1.0f / 60.0f;
		fixedDeltaTime = 1.0f / 50.0f;
		timeSinceStart = 0;
		frames = 0;
	}

	float ETime::CalculateFrameRate() {
		return frames / timeSinceStart * 1000.0f;
	}

	float ETime::GetTimeSinceBegining() {
		return timeSinceStart * 0.001;
	}

	float ETime::GetTimeSinceBeginingMilliseconds() {
		return timeSinceStart;
	}

	float ETime::GetFrameRate() {
		return CalculateFrameRate();
	}

	float ETime::GetDeltaTime() {
		return deltaTime;
	}

	float ETime::GetPhysicsDeltaTime() {
		return fixedDeltaTime;
	}

	std::string ETime::Time2String(float time) {

		float whole;

		int mill = std::modf(time, &whole) * 1000;

		int min = whole / 60;

		int sec = (int)whole % 60;

		std::stringstream stream;

		stream << std::setw(2) << std::setfill('0') << min << ":";
		stream << std::setw(2) << std::setfill('0') << sec << ":";
		stream << std::setw(3) << std::setfill('0') << mill;

		return stream.str();
	}

}