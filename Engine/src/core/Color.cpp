#include "Color.h"
#include <format>
#include <cassert>

namespace Core {

	Color Color::CreateColor(float r, float g, float b)
	{
		Color color;

		color.r = r;
		color.g = g;
		color.b = b;
		return color;
	}

	Color Color::Lerp(const Color& startColor, const Color& endColor, float t)
	{
		int r = std::round(std::lerp(startColor.r, endColor.r, t));
		int g = std::round(std::lerp(startColor.g, endColor.g, t));
		int b = std::round(std::lerp(startColor.b, endColor.b, t));
		return Color(r, g, b);
	}

	Color Color::Red()
	{
		return CreateColor(255, 0, 0);
	}

	Color Color::Green()
	{
		return CreateColor(0, 255, 0);
	}

	Color Color::Blue()
	{
		return CreateColor(0, 0, 255);
	}

	Color Color::Yellow()
	{
		return CreateColor(255, 255, 0);
	}

	Color Color::Purple()
	{
		return CreateColor(255, 0, 255);
	}

	Color Color::Orange()
	{
		return CreateColor(255, 165, 0);
	}

	Color Color::Black()
	{
		return CreateColor(0, 0, 0);
	}

	Color Color::White()
	{
		return CreateColor(255, 255, 255);
	}

	Color Color::Grey()
	{
		return CreateColor(200, 200, 200);
	}

	Color Color::Brown()
	{
		return CreateColor(60, 40, 20);
	}

	Color Color::DarkGrey()
	{
		return CreateColor(51, 51, 51);
	}

	Color::operator std::string() const {

		return std::format("({}, {}, {})", r, g, b);
	}

	std::ostream& operator<<(std::ostream& os, const Color& v)
	{
		os << (std::string)v;
		return os;
	}

	Color operator*(const Color& v, int n) {
		int R = v.r * n;
		int G = v.g * n;
		int B = v.b * n;

		return Color(R, G, B);
	}

}
