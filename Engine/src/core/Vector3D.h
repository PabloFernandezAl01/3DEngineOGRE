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

		Vector3D(float x, float y, float z) : x_(x), y_(y), z_(z) {}

		~Vector3D() {}

		// Getters
		inline float GetX() const { return x_; }
		inline float GetY() const { return y_; }
		inline float GetZ() const { return z_; }

		// Setters
		inline void SetX(float x) { x_ = x; }
		inline void SetY(float y) { y_ = y; }
		inline void SetZ(float z) { z_ = z; }

		// This is OGRE-dependent
		static inline Vector3D Forward() { return { 0, 0, -1 }; }
		static inline Vector3D Up() { return { 0, 1, 0 }; }
		static inline Vector3D Right() { return { 1, 0, 0 }; }

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

		inline Vector3D& operator=(const Vector3D& v) {
			x_ = v.x_;
			y_ = v.y_;
			z_ = v.z_;
			return *this;
		}

		// Multiply by a scalar
		inline Vector3D operator*(float scalar) const 
		{
			return { x_ * scalar, y_ * scalar, z_ * scalar };
		}

		inline Vector3D& operator*=(float scalar) 
		{
			x_ *= scalar;
			y_ *= scalar;
			z_ *= scalar;
			return *this;
		}

		// Division by  a scalar
		inline Vector3D operator/(float scalar) const 
		{
			return { x_ / scalar, y_ / scalar, z_ / scalar };
		}

		inline Vector3D& operator/=(float scalar)
		{
			x_ /= scalar;
			y_ /= scalar;
			z_ /= scalar;
			return *this;
		}

		// Addition
		inline Vector3D operator+(const Vector3D& v) const {
			return { x_ + v.x_, y_ + v.y_, z_ + v.z_ };
		}

		inline Vector3D& operator+=(const Vector3D& v) {
			x_ += v.x_;
			y_ += v.y_;
			z_ += v.z_;
			return *this;
		}

		// Subtraction
		inline Vector3D operator-(const Vector3D& v) const 
		{
			return { x_ - v.x_, y_ - v.y_, z_ - v.z_ };
		}

		inline Vector3D& operator-=(const Vector3D& v) 
		{
			x_ -= v.x_;
			y_ -= v.y_;
			z_ -= v.z_;
			return *this;
		}

		// Comparison operators
		inline bool operator==(const Vector3D& v) const {
			return x_ == v.x_ && y_ == v.y_ && z_ == v.z_;
		}

		inline bool operator!=(const Vector3D& v) const {
			return !(*this == v);
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

		inline float Dot(const Vector3D& v) const 
		{
			return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
		}

		inline Vector3D Cross(const Vector3D& v) const {
			return {
				y_ * v.z_ - z_ * v.y_,
				z_ * v.x_ - x_ * v.z_,
				x_ * v.y_ - y_ * v.x_
			};
		}

		inline Vector3D Lerp(const Vector3D& v, float p)
		{
			return { 
				(1 - p) * x_ + p * v.x_, 
				(1 - p) * y_ + p * v.y_, 
				(1 - p) * z_ + p * v.z_ 
			};
		}

		inline operator std::string() const {
			return "(" + std::to_string(x_) + "," + std::to_string(y_) + "," + std::to_string(z_) + ")";
		}

		float x_, y_, z_;
	};

	std::ostream& operator<<(std::ostream& os, const Vector3D& v);
}
