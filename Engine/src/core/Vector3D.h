#pragma once

#include <cmath>
#include <ostream>
#include <string>
#include <sstream>

namespace Core {

	class Vector3D {

	public:

		Vector3D() noexcept : x_(), y_(), z_() {}

		Vector3D(const Vector3D& v) : x_(v.GetX()), y_(v.GetY()), z_(v.GetZ()) {}

		Vector3D(const Vector3D* v) : x_(v->GetX()), y_(v->GetY()), z_(v->GetZ()) {}

		Vector3D(float x, float y, float z) : x_(x), y_(y), z_(z) {}

		Vector3D(const std::string& str) {
			std::stringstream ss(str);
			char discard;
			ss >> discard >> x_ >> discard >> y_ >> discard >> z_ >> discard;
		}

		Vector3D(const char* charArray) : Vector3D(std::string(charArray)) {}

		~Vector3D() {}

		// Getters
		inline float GetX() const { return x_; }
		inline float GetY() const { return y_; }
		inline float GetZ() const { return z_; }

		// Setters
		inline void SetX(float x) { x_ = x; }
		inline void SetY(float y) { y_ = y; }
		inline void SetZ(float z) { z_ = z; }

		inline void Set(float x, float y, float z) {
			x_ = x;
			y_ = y;
			z_ = z;
		}

		inline void Set(const Vector3D& v) {
			x_ = v.x_;
			y_ = v.y_;
			z_ = v.z_;
		}

		inline void Set(const Vector3D* v) {
			x_ = v->x_;
			y_ = v->y_;
			z_ = v->z_;
		}

		inline Vector3D& operator=(const Vector3D& v) {
			x_ = v.x_;
			y_ = v.y_;
			z_ = v.z_;
			return *this;
		}

		inline float Magnitude() const {
			return sqrtf(x_ * x_ + y_ * y_ + z_ * z_);
		}

		inline float SqrMagnitude() const {
			return x_ * x_ + y_ * y_ + z_ * z_;
		}

		inline Vector3D Normalize() const {
			float m = Magnitude();
			if (m == 0) return { 0, 0, 0 };
			return *this / m;
		}

		inline Vector3D Cross(const Vector3D& v) const {
			return Vector3D(
				y_ * v.z_ - z_ * v.y_,
				z_ * v.x_ - x_ * v.z_,
				x_ * v.y_ - y_ * v.x_
			);
		}

		inline float operator*(const Vector3D& v) const {
			return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
		}

		inline float Dot(const Vector3D& v) const {
			return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
		}

		inline Vector3D Mult(const Vector3D& v) const {
			return Vector3D(x_ * v.x_, y_ * v.y_, z_ * v.z_);
		}

		inline Vector3D operator+(const Vector3D& v) const {
			return Vector3D(x_ + v.x_, y_ + v.y_, z_ + v.z_);
		}

		inline Vector3D& operator+=(const Vector3D& v) {
			x_ += v.x_;
			y_ += v.y_;
			z_ += v.z_;
			return *this;
		}

		inline Vector3D operator-(const Vector3D& v) const {
			return Vector3D(x_ - v.x_, y_ - v.y_, z_ - v.z_);
		}

		inline Vector3D& operator-=(const Vector3D& v) {
			x_ -= v.x_;
			y_ -= v.y_;
			z_ -= v.z_;
			return *this;
		}

		inline Vector3D operator*(float scalar) const {
			return Vector3D(x_ * scalar, y_ * scalar, z_ * scalar);
		}

		inline Vector3D& operator*=(float scalar) {
			x_ *= scalar;
			y_ *= scalar;
			z_ *= scalar;
			return *this;
		}

		inline Vector3D operator/(float scalar) const {
			return Vector3D(x_ / scalar, y_ / scalar, z_ / scalar);
		}

		inline bool operator==(const Vector3D& v) const {
			return x_ == v.x_ && y_ == v.y_ && z_ == v.z_;
		}

		inline bool operator!=(const Vector3D& v) const {
			return !(*this == v);
		}

		inline float Volume() const {
			return x_ * y_ * z_;
		}

		inline operator std::string() const {
			return "(" + std::to_string(x_) + "," + std::to_string(y_) + "," + std::to_string(z_) + ")";
		}

		float x_, y_, z_;
	};

	std::ostream& operator<<(std::ostream& os, const Vector3D& v);
}
