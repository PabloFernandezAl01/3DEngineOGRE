#include "Vector3D.h"

std::ostream& Core::operator<<(std::ostream& os, const Vector3D& v) {
	os << "(" << v.x_ << ", " << v.y_ << ", " << v.z_ << ")";
	return os;
}
