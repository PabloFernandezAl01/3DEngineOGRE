#include "Assert.h"
#include "Log.h"
#include "EAssert.h"

void Core::EAssert::AssertConditionWithMessage(bool condition, CRefString conditionString, CRefString file, int line, CRefString function, CRefString message)
{
	if (!condition)
	{
		std::string msg = "[" + file + ":" + function + ":" + std::to_string(line) + "]";
		msg += "[" + conditionString + "] ";
		msg += message;

		Log::PrintError("", msg);
	}
}
