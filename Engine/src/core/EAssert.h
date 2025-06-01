#pragma once

#include "ETypes.h"

namespace Core
{
	class EAssert
	{
	public:

		static void AssertConditionWithMessage(bool condition, CRefString conditionString, CRefString file, int line, CRefString function, CRefString message);

	};
}

#define M_ASSERT(condition, message) Assert::AssertConditionWithMessage((condition), #condition, __FILE__, __LINE__, __FUNCTION__, message);
