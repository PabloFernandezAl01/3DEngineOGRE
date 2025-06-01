#include "Random.h"

#include <random>

#define PI 3.14159265f

namespace Utilities {

	int Random::RandomIntBetween(int min, int max) 
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(min, max);
		return dist(gen);
	}

	float Random::RandomBetween(float min, float max) 
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(min, max);
		return dist(gen);
	}

	float Random::RandomAngleBetween(float min, float max) 
	{
		float degree = Random::RandomBetween(min, max);

		return degree * PI / 180.0f;
	}

	Color Random::RandomColor() {
		Color c{};
		
		c.r = RandomIntBetween(0, 255);
		c.g = RandomIntBetween(0, 255);
		c.b = RandomIntBetween(0, 255);

		return c;
	}

	Color Random::RandomColorBetween(cColor c1, cColor c2) {
		Color c{};

		c.r = RandomIntBetween(c1.r, c2.r);
		c.g = RandomIntBetween(c1.g, c2.g);
		c.b = RandomIntBetween(c1.b, c2.b);

		return c;
	}

	Vector2D Random::RandomVectorBetween(cVector2D v1, cVector2D v2) {
		return { RandomBetween(v1.GetX(), v2.GetX()), RandomBetween(v1.GetY(), v2.GetY()) };
	}
}
