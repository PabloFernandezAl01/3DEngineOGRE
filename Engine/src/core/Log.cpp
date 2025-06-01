#include "Log.h"
#include "ETime.h"
#include <iostream>
#include <Windows.h>

void Log::Print(CRefString info, CRefString message)
{
	PrintColor(LogColor::LightBlue, LogColor::White, info, message);
}

void Log::PrintError(CRefString info, CRefString message)
{
	PrintColor(LogColor::LightRed, LogColor::White, "ERROR: " + info, message);
}

void Log::PrintWarning(CRefString info, CRefString message)
{
	PrintColor(LogColor::Yellow, LogColor::White, "WARNING: " + info, message);
}


void Log::PrintColor(LogColor infoColor, LogColor messageColor, CRefString info, CRefString message)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (int)infoColor);

	PrintInfo(info);

	SetConsoleTextAttribute(hConsole, (int)messageColor);

	std::cout << message << std::endl;

	SetConsoleTextAttribute(hConsole, (int)Color::White);
}


void Log::PrintInfo(CRefString info)
{
	std::string time = ETime::Time2String(ETime::Instance()->GetTimeSinceBegining());

	std::cout << "[" << time << "] ";

	if (info.size() > 0)
		std::cout << info << ": ";
}