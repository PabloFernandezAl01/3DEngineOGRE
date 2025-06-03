#include "Quaternion.h"

std::ostream& Core::operator<<(std::ostream& os, const Quaternion& q) {
	os << "(" << q.GetX() << ", " << q.GetY() << ", " << q.GetZ() << ", " << q.GetW() << ")";
	return os;
}

