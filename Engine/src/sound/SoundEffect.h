#pragma once

#include <ETypes.h>

struct Mix_Chunk;

namespace Sound {

	class SoundManager;

	class SoundEffect {

	public:

		SoundEffect(CRefString filepath);

		~SoundEffect();

		inline int GetSoundId() { return sound_id; }

	private:

		int sound_id{};

		Mix_Chunk* mix_chunk{};
	};

}

