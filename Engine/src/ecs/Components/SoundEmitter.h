#pragma once
#include "Component.h"
#include <ETypes.h>
#include <vector>

namespace Sound {
	class SoundEffect;
	class SoundManager;
}

namespace ECS {

	class Transform;

	class SoundEmitter : public Component {

	public:

		SoundEmitter();

		~SoundEmitter();

		// Select another sound asset
		void LoadSound(CRefString fileName);

		// Plays the current sound
		void Play();

		// Pause the current sound. Can be resumed
		void Pause();

		// Stop the current sound. Can not be resumed
		void Stop();

		// If the sound is paused, resumes it
		void Resume();

		// Plays the sound with fade in for (float seconds)
		// Loops-> Times the sound will repeat, -1 to "Infinitely", 0 to repeat just once
		void PlayWithfadeIn(int seconds, int loops = -1);

		// Fade out the sound for (float) seconds
		void FadeOut(int seconds);

		// Returns true if this component has the sound playing, false otherwise
		bool IsPlaying();

		// Returns true if this component has the sound paused, false otherwise
		bool IsPaused();

		// Sets the volume of the sound in this component
		// Value must be between 0 and 1
		void SetVolume(float volume);
		
		// Gets the volume of the sound in this component
		// Returned value is betwween 0 and 1
		inline int GetVolume() { return volume; }

		// Set true if you want to play the music at the 
		// start of the scene, false otherwise
		inline void ShouldPlayOnStart(bool play) { this->playOnStart = play; }

		// Set true if you want to play the sound on loop, 
		// false otherwise
		inline void SetLoop(bool loop) { this->loop = loop; }

		// Returns true if the sound is playing on loop,
		// false otherwise
		inline bool IsOnLoop() { return loop; }

		// Set true to enable the spatial sound 
		// based on the camera position
		inline void EnableSpatialSound(bool enable) { this->spatialSound = enable; }

		// Returns true if spatial sound is enabled
		inline bool IsSpatialSoundEnabled() { return spatialSound; }

		// Sets the panning value, 0 to apply sound
		// only on the left channel, 1 to apply only on the right one
		void SetPanning(float panning);

		// Return a value between 0 and 1 representing
		// how sound is played on left and right channels
		inline float GetPanning() { return panning; }

		// Sets the distance at which sound ceases to be audible
		inline void SetAudibleDistance(float distance) { this->audibleDistance = distance; }

		// Gets the distance at which sound ceases to be audible
		inline float GetAudibleDistance() { return audibleDistance; }

	private:

		void Init() override;

		void Start() override;

		void Update(float deltaTime) override;

		void DisableEmittersOnSameChannel();

		void ApplyPanning();

		std::string fileName;
		bool loop{};
		bool playOnStart{};
		float volume{ .5f };
		bool spatialSound{ true };
		float panning{ .5f };
		float audibleDistance{};

		static std::vector<SoundEmitter*> soundEmitters;

		Transform* transform{};

		Sound::SoundEffect* soundEffect{};

		Sound::SoundManager* sManager{};

		float angle{};
		int channel{ -1 };
		int sound_id{};
		bool onChannel{};

	};


}