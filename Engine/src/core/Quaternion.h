#pragma once

#include <cmath>
#include <ostream>
#include <string>
#include <numbers>
#include "Vector3D.h"

namespace Core {

	class Quaternion {
	public:
		// Constructores
		Quaternion() noexcept : x_(0.0f), y_(0.0f), z_(0.0f), w_(1.0f) {}

		Quaternion(float x, float y, float z, float w) : x_(x), y_(y), z_(z), w_(w) {}

		// Construcción desde eje y ángulo (en grados)
		Quaternion(const Vector3D& axis, float angleDeg) {
			float radians = angleDeg * (std::numbers::pi / 180.0f);
			float halfAngle = radians / 2.0f;
			float s = std::sinf(halfAngle);

			Vector3D normAxis = axis.Normalize();
			x_ = normAxis.x_ * s;
			y_ = normAxis.y_ * s;
			z_ = normAxis.z_ * s;
			w_ = std::cosf(halfAngle);
		}

		float GetX() const { return x_; }
		float GetY() const { return y_; }
		float GetZ() const { return z_; }
		float GetW() const { return w_; }

		void SetX(float x) { x_ = x; }
		void SetY(float y) { y_ = y; }
		void SetZ(float z) { z_ = z; }
		void SetW(float w) { w_ = w; }

		static Quaternion Identity() {
			return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		}

		static float DegreesToRadians(float degrees)
		{
			return degrees * (std::numbers::pi / 180.0f);
		}

		// Quaternion multiplication
		Quaternion operator*(const Quaternion& q) const
		{
			float ps = w_;
			Vector3D qv{ q.x_, q.y_, q.z_ };
			float qs = q.w_;
			Vector3D pv{ x_, y_, z_ };

			Vector3D resV = qv * ps + pv * qs + pv.Cross(qv);
			float resS = ps * qs - pv.Dot(qv);

			return { resV.x_, resV.y_, resV.z_, resS };
		}

		// Quaternion division
		Quaternion operator/(const Quaternion& q) const {
			return (*this) * q.Inverse();
		}

		// Division by a scalar
		Quaternion operator/(float scalar) const {
			if (std::fabs(scalar) < 0.00001f) return Quaternion();
			return Quaternion(x_ / scalar, y_ / scalar, z_ / scalar, w_ / scalar);
		}

		Quaternion Conjugate() const {
			return Quaternion(-x_, -y_, -z_, w_);
		}

		// Inversa
		Quaternion Inverse() const {
			float sqrMag = x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;
			if (sqrMag <= 0.00001f) return Quaternion();
			return Conjugate() / sqrMag;
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

		
		// Rotación de vector with a Quaternion
		Vector3D Rotate(const Vector3D& vector) const {
			Quaternion v(vector.x_, vector.y_, vector.z_, 0.0f);
			Quaternion result = (*this) * v * Inverse();
			return Vector3D(result.x_, result.y_, result.z_);
		}

		Vector3D operator*(const Vector3D& v) const
		{
			return Rotate(v);
		}

		// Conversion from euler angles (yaw, pitch, roll) to quaternion
		// (IN DEGREES)
		static Quaternion FromEulerAngles(const Vector3D& eulerAngles)
		{
			Vector3D anglesInRadians{ DegreesToRadians(eulerAngles.GetX()), DegreesToRadians(eulerAngles.GetY()), DegreesToRadians(eulerAngles.GetZ()) };

			float halfX = anglesInRadians.GetX() * 0.5f; // pitch
			float halfY = anglesInRadians.GetY() * 0.5f; // yaw
			float halfZ = anglesInRadians.GetZ() * 0.5f; // roll

			float cx = cos(halfX);
			float sx = sin(halfX);
			float cy = cos(halfY);
			float sy = sin(halfY);
			float cz = cos(halfZ);
			float sz = sin(halfZ);

			Quaternion q;
			q.w_ = cx * cy * cz + sx * sy * sz;
			q.x_ = sx * cy * cz - cx * sy * sz;
			q.y_ = cx * sy * cz + sx * cy * sz;
			q.z_ = cx * cy * sz - sx * sy * cz;

			return q;
		}

		// Spherical Linear Interpolation (SLERP)
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t) {

			// Compute the cosine of the angle between the two quaternions
			float dot = a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_ + a.w_ * b.w_;

			Quaternion end = b;

			// If dot < 0, the interpolation will take the long way around the sphere.
			// To fix this, one quaternion must be negated.
			if (dot < 0.0f) {
				dot = -dot;
				end = Quaternion(-b.x_, -b.y_, -b.z_, -b.w_);
			}

			const float DOT_THRESHOLD = 0.9995f;
			if (dot > DOT_THRESHOLD) {
				// If the quaternions are very close, use linear interpolation
				Quaternion result = Quaternion(
					a.x_ + t * (end.x_ - a.x_),
					a.y_ + t * (end.y_ - a.y_),
					a.z_ + t * (end.z_ - a.z_),
					a.w_ + t * (end.w_ - a.w_)
				);
				return result.Normalize();
			}

			// Since dot is in range [0, DOT_THRESHOLD], acos is safe
			float theta_0 = std::acos(dot);        // angle between input quaternions
			float theta = theta_0 * t;             // angle between a and result
			float sin_theta = std::sin(theta);
			float sin_theta_0 = std::sin(theta_0);

			float s0 = std::cos(theta) - dot * sin_theta / sin_theta_0;
			float s1 = sin_theta / sin_theta_0;

			return Quaternion(
				(a.x_ * s0) + (end.x_ * s1),
				(a.y_ * s0) + (end.y_ * s1),
				(a.z_ * s0) + (end.z_ * s1),
				(a.w_ * s0) + (end.w_ * s1)
			);
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
