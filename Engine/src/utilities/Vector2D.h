#pragma once

#include <cmath>
#include <ostream>
#include <string>

/*
 * A class implementing a 2-dimensional vector and corresponding
 * operations. All operations generate new Vector2D, they do not
 * modify the vectors on which they operate. The only methods that
 * modify the state are the different setters (and operator=).
 */

namespace Utilities {

	class Vector2D {

	public:

		// Various constructors
		Vector2D() noexcept :
			x_(), y_() {
		}

		// Construct a Vector2D given a string representing its value ("(2, 1)", "3, 1")
		Vector2D(std::string const& str);
		Vector2D(const char* charArray);

		Vector2D(const Vector2D& v) :
			x_(v.GetX()), y_(v.GetY()) {
		}

		Vector2D(const Vector2D* v) :
			x_(v->GetX()), y_(v->GetY()) {
		}

		Vector2D(float x, float y) :
			x_(x), y_(y) {
		}

		~Vector2D() {
		}

		// various getters
		inline float GetX() const {
			return x_;
		}

		inline float GetY() const {
			return y_;
		}

		// various setters
		inline void SetX(float x) {
			x_ = x;
		}

		inline void SetY(float y) {
			y_ = y;
		}

		inline void Set(float x, float y) {
			x_ = x;
			y_ = y;
		}

		inline void Set(const Vector2D& v) {
			x_ = v.x_;
			y_ = v.y_;
		}

		inline void Set(const Vector2D* v) {
			x_ = v->x_;
			y_ = v->y_;
		}

		// copy assignment
		inline Vector2D& operator=(const Vector2D& v) {
			x_ = v.x_;
			y_ = v.y_;
			return *this;
		}

		// ** various operations

		// Length of the vector
		inline float Magnitude() const {
			return sqrtf(powf(x_, 2) + powf(y_, 2));
		}

		// Square length of the vector
		inline float SqrMagnitude() const {
			return x_ * x_ + y_ * y_;
		}

		// Vector in the same direction of length 1
		inline Vector2D Normalize() const {

			float m = Magnitude();

			if (m == 0) return {0, 0};

			return *this / m;
		}

		inline float Area() const {
			return x_ * y_;
		}

		// Counter clockwise rotation in a normal coordinate system, and
		// it is clockwise rotation if we work with a coordinate system
		// in which the vertical axe is flipped (it is like a mirror over
		// the horizontal axe)-- which the case when working with the SDL.
		//
		Vector2D Rotate(float degrees) const;

		// Computes the angle between 'this' and 'v'. The result is
		// between -180 and 180, and is such that the following holds:
		//
		//   this->rotate(angle) == v
		//
		float Angle(const Vector2D& v) const;

		// Vector subtraction
		inline Vector2D operator-(const Vector2D& v) const {
			return Vector2D(x_ - v.x_, y_ - v.y_);
		}

		inline Vector2D operator-=(const Vector2D& v) {
			x_ -= v.x_;
			y_ -= v.y_;
			return *this;
		}

		// Vector addition
		inline Vector2D operator+(const Vector2D& v) const {
			return Vector2D(x_ + v.x_, y_ + v.y_);
		}

		inline Vector2D operator+=(const Vector2D& v) {
			x_ += v.x_;
			y_ += v.y_;
			return *this;
		}

		inline bool operator!=(const Vector2D& v) {
			return x_ != v.x_ || y_ != v.y_;
		}

		inline bool operator==(const Vector2D& v) {
			return x_ == v.x_ && y_ == v.y_;
		}

		// Multiplication by constant (scaling)
		inline Vector2D operator*(float d) const {
			return Vector2D(x_ * d, y_ * d);
		}

		// Multiplication by constant (scaling)
		inline Vector2D operator*=(float d) const {
			return Vector2D(x_ * d, y_ * d);
		}

		inline Vector2D operator*=(float d) {
			x_ *= d;
			y_ *= d;
			return *this;
		}

		inline Vector2D operator*=(const Vector2D& v) {
			x_ *= v.x_;
			y_ *= v.y_;
			return *this;
		}

		// Division by constant (scaling)
		inline Vector2D operator/(float d) const {
			return Vector2D(x_ / d, y_ / d);
		}

		// Scalar multiplication
		inline float operator*(const Vector2D& d) const {
			return d.x_ * x_ + d.y_ * y_;
		}

		// Scalar multiplication
		inline Vector2D Mult(const Vector2D& d) const {
			return Vector2D(d.x_ * x_ , d.y_ * y_);
		}


		inline operator std::string() const{
			return "(" + std::to_string(x_)+ "," + std::to_string(y_) + ")";
		}


		float x_;  // first coordinate
		float y_;  // second coordinate
	};

	// Needed for printing a value of type Vector2D with std::cout.
	// The definition is in .cpp
	std::ostream& operator<<(std::ostream& os, const Vector2D& v);

}

using cVector2D = Utilities::Vector2D const&;
