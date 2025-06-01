#include "ConsoleManager.h"
#include <iostream>
#include <Windows.h>
#include "ETime.h"

using namespace Utilities;

void Console::Output::Print(CRefString info, CRefString message)
{
	PrintColor(Color::LightBlue, Color::White, info, message);
}

void Console::Output::PrintError(CRefString info, CRefString message)
{
	PrintColor(Color::LightRed, Color::White, "ERROR: " + info, message);
}

void Console::Output::PrintWarning(CRefString info, CRefString message)
{
	PrintColor(Color::Yellow, Color::White, "WARNING: " + info, message);
}


void Console::Output::PrintColor(Color infoColor, Color messageColor, CRefString info, CRefString message)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (int)infoColor);

	PrintInfo(info);

	SetConsoleTextAttribute(hConsole, (int)messageColor);

	std::cout << message << std::endl;

	SetConsoleTextAttribute(hConsole, (int)Color::White);
}


void Console::Output::PrintInfo(CRefString info)
{
	std::string time = ETime::Time2String(ETime::Instance()->GetTimeSinceBegining());

	std::cout << "[" << time << "] ";

	if (info.size() > 0)
		std::cout << info << ": ";
}


void Console::Output::PrintNoFormat(CRefString message, Color color)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (int)color);

	std::cout << message << std::endl;

	SetConsoleTextAttribute(hConsole, (int)Color::White);
}