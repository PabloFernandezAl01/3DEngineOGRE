#pragma once

#include <cmath>
#include <ostream>
#include <string>
#include "Vector3D.h"

namespace Core {

	class Quaternion {
	public:
		// Constructores
		Quaternion() noexcept : x_(0.0f), y_(0.0f), z_(0.0f), w_(1.0f) {}

		Quaternion(float x, float y, float z, float w) :
			x_(x), y_(y), z_(z), w_(w) {}

		// Construcción desde eje y ángulo (en grados)
		Quaternion(const Vector3D& axis, float angleDeg) {
			constexpr float DegToRad = 3.14159265358979323846f / 180.0f;
			float angleRad = angleDeg * DegToRad;
			float halfAngle = angleRad / 2.0f;
			float s = std::sinf(halfAngle);

			Vector3D normAxis = axis.Normalize();
			x_ = normAxis.x_ * s;
			y_ = normAxis.y_ * s;
			z_ = normAxis.z_ * s;
			w_ = std::cosf(halfAngle);
		}

		// Getters
		float GetX() const { return x_; }
		float GetY() const { return y_; }
		float GetZ() const { return z_; }
		float GetW() const { return w_; }

		// Setters
		void SetX(float x) { x_ = x; }
		void SetY(float y) { y_ = y; }
		void SetZ(float z) { z_ = z; }
		void SetW(float w) { w_ = w; }

		// Cuaternión identidad
		static Quaternion Identity() {
			return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		}

		// Desde eje y ángulo en radianes
		static Quaternion FromAxisAngle(const Vector3D& axis, float angleRad) {
			float halfAngle = angleRad * 0.5f;
			float s = std::sinf(halfAngle);

			Vector3D normAxis = axis.Normalize();
			return Quaternion(
				normAxis.x_ * s,
				normAxis.y_ * s,
				normAxis.z_ * s,
				std::cosf(halfAngle)
			);
		}

		// Desde rotación entre dos vectores
		static Quaternion FromRotationBetween(const Vector3D& from, const Vector3D& to) {
			Vector3D f = from.Normalize();
			Vector3D t = to.Normalize();

			float dot = f.Dot(t);

			// Si los vectores son casi iguales
			if (dot > 0.9999f) {
				return Identity();
			}
			// Si los vectores son opuestos
			else if (dot < -0.9999f) {
				Vector3D orthogonal = Vector3D(1, 0, 0).Cross(f);
				if (orthogonal.Magnitude() < 0.0001f) {
					orthogonal = Vector3D(0, 1, 0).Cross(f);
				}
				orthogonal = orthogonal.Normalize();
				return FromAxisAngle(orthogonal, 3.14159265358979323846f); // Pi rad
			}
			else {
				Vector3D axis = f.Cross(t);
				float s = std::sqrt((1 + dot) * 2);
				float invS = 1.0f / s;
				return Quaternion(
					axis.x_ * invS,
					axis.y_ * invS,
					axis.z_ * invS,
					s * 0.5f
				).Normalize();
			}
		}

		float Dot(const Vector3D& other) const {
			return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
		}

		Vector3D Cross(const Vector3D& other) const {
			return Vector3D(
				y_ * other.z_ - z_ * other.y_,
				z_ * other.x_ - x_ * other.z_,
				x_ * other.y_ - y_ * other.x_
			);
		}

		// Rotación de vector con operador *
		Vector3D operator*(const Vector3D& v) const {
			return Rotate(v);
		}

		// Conjugado
		Quaternion Conjugate() const {
			return Quaternion(-x_, -y_, -z_, w_);
		}

		// Norma
		float Magnitude() const {
			return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
		}

		// Normalización
		Quaternion Normalize() const {
			float mag = Magnitude();
			if (mag <= 0.00001f) return Quaternion();
			return Quaternion(x_ / mag, y_ / mag, z_ / mag, w_ / mag);
		}

		// Inversa
		Quaternion Inverse() const {
			float sqrMag = x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;
			if (sqrMag <= 0.00001f) return Quaternion();
			return Conjugate() / sqrMag;
		}

		// Multiplicación de quaterniones
		Quaternion operator*(const Quaternion& q) const {
			return Quaternion(
				w_ * q.x_ + x_ * q.w_ + y_ * q.z_ - z_ * q.y_,
				w_ * q.y_ - x_ * q.z_ + y_ * q.w_ + z_ * q.x_,
				w_ * q.z_ + x_ * q.y_ - y_ * q.x_ + z_ * q.w_,
				w_ * q.w_ - x_ * q.x_ - y_ * q.y_ - z_ * q.z_
			);
		}

		// División por escalar
		Quaternion operator/(float scalar) const {
			if (std::fabs(scalar) < 0.00001f) return Quaternion();
			return Quaternion(x_ / scalar, y_ / scalar, z_ / scalar, w_ / scalar);
		}

		// Rotación de vector
		Vector3D Rotate(const Vector3D& v) const {
			Quaternion qv(v.x_, v.y_, v.z_, 0.0f);
			Quaternion result = (*this) * qv * Inverse();
			return Vector3D(result.x_, result.y_, result.z_);
		}

		// Conversión a string
		std::string ToString() const {
			return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ", " +
				std::to_string(z_) + ", " + std::to_string(w_) + ")";
		}

	private:
		float x_{}, y_{}, z_{}, w_{};
	};

	// Impresión por consola
	inline std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
		return os << q.ToString();
	}
}
