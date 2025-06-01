#include "SoundEffect.h"
#include "SoundManager.h"
#include "SDL_mixer.h"

#include <ConsoleManager.h>

namespace Sound {

	SoundEffect::SoundEffect(CRefString filepath) 
	{
		mix_chunk = Mix_LoadWAV(filepath.c_str());

		if (mix_chunk == nullptr) 
		{
			Console::Output::PrintError("Invalid argument value", Mix_GetError());
			sound_id = 0;
			return;
		}

		sound_id = SoundManager::Instance()->LoadSoundEffect(mix_chunk);
	}

	SoundEffect::~SoundEffect()
	{
		Mix_FreeChunk(mix_chunk);
	}
}
