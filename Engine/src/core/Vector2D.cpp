#include "Vector2D.h"
#include "StringTrim.h"
#include <cassert>
#include <string>
#include <numbers>

namespace Core {

	// Printing a Vector2D
	std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
		os << "(" << v.GetX() << "," << v.GetY() << ")";
		return os;
	}

	Vector2D Vector2D::Rotate(float degrees) const {
		Vector2D r;

		degrees = fmod(degrees, 360.0f);
		if (degrees > 180.0f) {
			degrees = degrees - 360.0f;
		}
		else if (degrees <= -180.0f) {
			degrees = 360.0f + degrees;
		}

		float angle = degrees * std::numbers::pi / 180.0f;
		float sine = sin(angle);
		float cosine = cos(angle);

		//rotation matrix
		float matrix[2][2] = { { cosine, -sine }, { sine, cosine } };

		float x = x_;
		float y = y_;

		r.x_ = matrix[0][0] * x + matrix[0][1] * y;
		r.y_ = matrix[1][0] * x + matrix[1][1] * y;

		return r;
	}

	float Vector2D::Angle(const Vector2D& v) const {
		float a2 = atan2(v.GetX(), v.GetY());
		float a1 = atan2(x_, y_);
		float angle = a1 - a2;
		float K = a1 > a2 ? -2.0f * std::numbers::pi : 2.0f * std::numbers::pi;
		angle = (abs(K + angle) < abs(angle)) ? K + angle : angle;
		return angle * 180.0f / std::numbers::pi;
	}

	Vector2D::Vector2D(std::string const& str) {

		std::string trimed = Core::trim(str, "([ )]");

		size_t coma = trimed.find(",");

		assert(coma != std::string::npos);

		std::string x = trimed.substr(0, coma);
		std::string y = trimed.substr(coma + 1);

		x_ = std::stof(x);
		y_ = std::stof(y);
	}
}
