#pragma once

#include <string>
#include <ETypes.h>

namespace Console {

	enum class Color {

		Black, DeepBlue, DarkGreen, LightBlue, Red, Purple, Yellow, LightGrey, Grey, Blue, Green, Aqua, LightRed, LightPurple, LightYellow, White
	};

	class Output {

	public:

		static void Print(CRefString info, CRefString message);

		static void PrintError(CRefString info, CRefString message);

		static void PrintWarning(CRefString info, CRefString message);

		static void PrintNoFormat(CRefString message, Color color = Color::White);

	private:

		static void PrintColor(Color infoColor, Color messageColor, CRefString info, CRefString message);

		static void PrintInfo(CRefString info);

	};

}

