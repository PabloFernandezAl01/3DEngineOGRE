#pragma once

#include "EditorExport.h"
#include "Singleton.h"
#include "ConfigManager.h"
#include "SDL_mixer.h"
#include <string>
#include <vector>

class Engine;

namespace Sound {

	class SoundManager : public Utilities::Singleton<SoundManager> {

		friend Singleton<SoundManager>;
		friend Engine;

	public:

		~SoundManager();

		// Sets the master volume (affects music and sound channels)
		// Volume should be between 0 and 1
		void SetMasterVolume(float volume);

		// Channels

			// Load a sound into the vector
			int LoadSoundEffect(Mix_Chunk* s);

			// Play a sound specifying a channel. -1 to find the first available channel.
			// Returns the selected channel or -1 if sound could not be played
			int PlaySound(int id, int loop, int channel = -1);

			// Play a sound with fade in specifying a channel. -1 to find the first available channel
			int FadeInChannel(int channel, int id, int loops, int ms);

			// Play a sound with fade out specifying a channel. -1 to find the first available channel
			void FadeOutChannel(int channel, int ms);

			void StopChannel(int channel);

			// Pause a particular channel
			void PauseChannel(int channel);

			// Return 1 if channel is paused, 0 otherwise
			bool PausedChannel(int channel);

			// Resume a channel
			void ResumeChannel(int channel);

			// Returns non-zero if channel is playing, zero otherwise.
			bool IsChannelPlaying(int channel);

			// Set volume to a channel. Volume is between 0 and 128
			void SetChannelVolume(int channel, int volume);

			// Get a channel volume. Return value is between 0 and 128
			int GetChannelVolume(int channel);

			// Sets the position of the cannel relative to the listener. Angle is between 0-360 and distance is between 0-255
			void SetChannelPosition(int channel, int angle, int distance);

			// Sets the panning of the channel
			void SetChannelPanning(int channel, int left, int right);

		// Music

			// Load a music into the vector
			int LoadMusic(Mix_Music* m);

			// No need to specify a channel, music has only 1 channel
			void PlayMusic(int id, int loop);

			// Play the music with ms of fade in
			void FadeInMusic(int id, int loops, int ms);

			// Halt the music channel after fading out for ms
			void FadeOutMusic(int ms);

			// Pause the music channel. It can be resumed
			void PauseMusic();

			// Returns 1 if music is paused, 0 otherwise
			bool MusicPaused();

			// Stop the actual music object so music it's paused and it can not be resumed. User needs to create a new music object
			void HaltMusic();

			// Resume the music channel
			void ResumeMusic();

			// Returns 1 if music is playing, 0 otherwise
			bool IsMusicPlaying();

			// Set the music channel volume.  Volume is between 0 and 128
			void SetMusicVolume(int volume);

			// Gets the music channel volume. Return value is between 0 and 128
			int GetMusicVolume();

			// Rewinds the music
			void RewindMusic();
		
	private:

		SoundManager() {};
		SoundManager(const ConfigData& data);

		bool Valid() override;

		bool InitSDLMixer(int frequency, int channels, int chunksize);
		void CloseSDLMixer();

		// Sets the number of channels handled by the audio engine
		void SetChannelsCapacity(float nChannels);

		int nChannels{};

		std::vector<Mix_Chunk*> sfxs{};
		std::vector<Mix_Music*> music{};

		bool valid{};
	};
}