#pragma once

#include "SDL_mixer.h"
#include <ETypes.h>

namespace Sound {

	class SoundManager;

	class Music {

	public:

		Music(CRefString filepath);

		~Music();

		inline int GetMusicId() { return music_id; }

	private:

		SoundManager* soundManager{};

		int music_id{};

		Mix_Music* mix_music{};

	};

}

