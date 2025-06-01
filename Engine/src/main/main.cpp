#include <iostream>
#include <memory>

#include "Engine.h"

/*
* This is a way to avoid opening the debug console in release mode.
*/

#ifdef _DEBUG

	int main(int argc, char* args[]) {

#else

	#include <Windows.h>

	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, int nCmdShow) {

#endif

		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		Engine engine;

		bool ret = engine.Init();

		if (!ret) {
			return -1;
		}

		engine.Update();

		engine.Close();

		return 0;
	}
