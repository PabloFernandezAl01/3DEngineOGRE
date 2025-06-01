#include "Music.h"
#include "SoundManager.h"

#include <ConsoleManager.h>

namespace Sound {

	Music::Music(CRefString filepath)
	{
		soundManager = Sound::SoundManager::Instance();

		mix_music = Mix_LoadMUS(filepath.c_str());

		if (mix_music == nullptr)
		{
			Console::Output::PrintError("Invalid argument value", Mix_GetError());
			music_id = 0;
			return;
		}

		music_id = soundManager->LoadMusic(mix_music);
	}

	Music::~Music()
	{
		Mix_FreeMusic(mix_music);
	}

}
