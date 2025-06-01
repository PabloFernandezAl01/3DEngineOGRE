#pragma once

#include "ETypes.h"

namespace Core
{
	class Log
	{

	enum class LogColor { LightBlue, Yellow, Aqua, LightRed, White };

	public:

		Log() = default;
		~Log() = default;

		static void Print(CRefString info, CRefString message);

		static void PrintError(CRefString info, CRefString message);

		static void PrintWarning(CRefString info, CRefString message);

	private:

		static void PrintColor(LogColor infoColor, LogColor messageColor, CRefString info, CRefString message);

		static void PrintInfo(CRefString info);
	};
}
