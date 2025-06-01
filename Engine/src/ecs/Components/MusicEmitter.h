#pragma once

#include "Component.h"
#include <ETypes.h>
#include <vector>

namespace Sound {
    class Music;
    class SoundManager;
}

namespace ECS {

    class Transform;

    class MusicEmitter : public Component {

    public:

        MusicEmitter();

        ~MusicEmitter();

		// Select another music asset
		void LoadMusic(CRefString fileName);

        // Plays the current music
        void Play();

        // Pause the current music. Can be resumed
        void Pause();

        // Stop the current music. Can not be resumed
        void Stop();

        // If music is paused, resumes the music
        void Resume();

        // Plays the music with fade in for (float seconds)
        // Loops-> Times music will repeat, -1 to "Infinitely", 0 to repeat just once
        void PlayWithFadeIn(float seconds, int loops = -1);

        // Fade out the music for (float) seconds
        void FadeOut(float seconds);

        // Returns true if this component has the music playing, false otherwise
        bool IsPlaying();

        // Returns true if this component has the music paused, false otherwise
        bool IsPaused();

        // Rewind the music from the beginning
        void Rewind();

        // Sets the volume of the music in this component
        // Value must be between 0 and 1
        void SetVolume(float volume);

        // Gets the volume of the music in this component
        // Returned value is betwween 0 and 1
        inline float GetVolume() { return volume; }

        // Set true if you want to play the music at the 
        // start of the scene, false otherwise
        inline void ShouldPlayOnStart(bool play) { playOnStart = play; }

        // Set true if you want to play the music on loop, 
        // false otherwise
        inline void SetLoop(bool loop) { this->loop = loop; }

        // Returns true if the music is playing on loop,
        // false otherwise
        inline bool IsOnLoop() { return loop; }

    private:

        void Init() override;

        void Start() override;

        std::string fileName{};
        bool loop{};
        bool playOnStart{ true };
        float volume{ .5f };

        Sound::SoundManager* sManager{};

        Transform* transform{};

        Sound::Music* music{};

        static MusicEmitter* emitterOnChannel;

        bool onChannel{};

        int music_id{};

    };
}

