#pragma once

#include <string>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "Color.h"

namespace Core
{
	using CRefString = const std::string&;
	using CRefVector2D = const Core::Vector2D&;
	using CRefVector3D = const Core::Vector3D&;
	using CRefQuaternion = const Core::Quaternion&;
	using CRefColor = const Core::Color&;
}

using namespace Core;

