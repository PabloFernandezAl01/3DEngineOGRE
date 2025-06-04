#pragma once

#include <cmath>
#include <ostream>
#include <string>
#include "Vector3D.h"

#define M_PI 3.14159265358979323846264338327

namespace Core {

	class Quaternion {

	public:

		// Constructores
		Quaternion() noexcept : x_(0), y_(0), z_(0), w_(1) {}

		Quaternion(float x, float y, float z, float w) :
			x_(x), y_(y), z_(z), w_(w) {}

		// Construcción desde eje y ángulo (en grados)
		Quaternion(const Vector3D& axis, float angleDeg) {
			float angleRad = angleDeg * (float)M_PI / 180.0f;
			float halfAngle = angleRad / 2.0f;
			float s = sinf(halfAngle);

			Vector3D normAxis = axis.Normalize();
			x_ = normAxis.x_ * s;
			y_ = normAxis.y_ * s;
			z_ = normAxis.z_ * s;
			w_ = cosf(halfAngle);
		}

		float GetX() const { return x_; }
		float GetY() const { return y_; }
		float GetZ() const { return z_; }
		float GetW() const { return w_; }

		void SetX(float x) { x_ = x; }
		void SetY(float y) { y_ = y; }
		void SetZ(float z) { z_ = z; }
		void SetW(float w) { w_ = w; }

		// Conjugado
		Quaternion Conjugate() const {
			return Quaternion(-x_, -y_, -z_, w_);
		}

		// Norma
		float Magnitude() const {
			return sqrtf(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
		}

		// Normalización
		Quaternion Normalize() const {
			float mag = Magnitude();
			if (mag == 0) return Quaternion();
			return Quaternion(x_ / mag, y_ / mag, z_ / mag, w_ / mag);
		}

		// Inversa (conjugado / |q|^2)
		Quaternion Inverse() const {
			float sqrMag = x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;
			if (sqrMag == 0) return Quaternion();
			return Conjugate() / sqrMag;
		}

		// Operador de multiplicación de quaterniones (q1 * q2)
		Quaternion operator*(const Quaternion& q) const {
			return Quaternion(
				w_ * q.x_ + x_ * q.w_ + y_ * q.z_ - z_ * q.y_,
				w_ * q.y_ - x_ * q.z_ + y_ * q.w_ + z_ * q.x_,
				w_ * q.z_ + x_ * q.y_ - y_ * q.x_ + z_ * q.w_,
				w_ * q.w_ - x_ * q.x_ - y_ * q.y_ - z_ * q.z_
			);
		}

		// Escalar
		Quaternion operator/(float scalar) const {
			return Quaternion(x_ / scalar, y_ / scalar, z_ / scalar, w_ / scalar);
		}

		// Rotar un vector
		Vector3D Rotate(const Vector3D& v) const {
			Quaternion qv(v.x_, v.y_, v.z_, 0);
			Quaternion result = (*this) * qv * Inverse();
			return Vector3D(result.x_, result.y_, result.z_);
		}

		// Conversión a string
		operator std::string() const {
			return "(" + std::to_string(x_) + "," + std::to_string(y_) + "," + std::to_string(z_) + "," + std::to_string(w_) + ")";
		}

	private:

		// Componentes (x, y, z) vectorial, w escalar
		float x_{}, y_{}, z_{}, w_{};
	};

	// Impresión por consola
	std::ostream& operator<<(std::ostream& os, const Quaternion& q);
}
