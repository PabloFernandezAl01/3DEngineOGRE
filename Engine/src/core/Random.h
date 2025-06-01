#pragma once

#include "ETypes.h"

namespace Core {

	class Random {

	public:

		// Returns a random integer between min and max.
		static int RandomIntBetween(int min, int max);

		// Returns a random float between min and max.
		static float RandomBetween(float min, float max);

		// Returns a random angle between two given values (in degrees).
		static float RandomAngleBetween(float min, float max);

		// Generates a random color.
		static Color RandomColor();

		// Generates a random color among the given ones.
		static Color RandomColorBetween(CRefColor c1, CRefColor c2);

		// Generates a random color among the given ones.
		static Vector2D RandomVectorBetween(CRefVector2D v1, CRefVector2D v2);

	};

}

