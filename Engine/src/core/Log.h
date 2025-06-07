#pragma once

#include "ETypes.h"

namespace Core
{
	class Log
	{

	enum class LogColor { Black, DeepBlue, DarkGreen, LightBlue, Red, Purple, Yellow, LightGrey, Grey, Blue, Green, Aqua, LightRed, LightPurple, LightYellow, White };

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
