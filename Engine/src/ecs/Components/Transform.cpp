#include "Transform.h"
#include "Vector2D.h"

#include "Entity.h"

namespace ECS {

	Transform::Transform(CRefVector2D position, CRefVector2D scale, float rotation) : position(position), scale(scale), rotation(rotation) {}
}