#include "MusicEmitter.h"
#include "Transform.h"
#include "Entity.h"
#include "Music.h"

#include <ResourcesManager.h>
#include <ConsoleManager.h>
#include <SoundManager.h>

namespace ECS {
	
	MusicEmitter* MusicEmitter::emitterOnChannel = nullptr;

	MusicEmitter::MusicEmitter()
	{
		sManager = Sound::SoundManager::Instance();
	}

	MusicEmitter::~MusicEmitter() 
	{
		Stop();
	}

	void MusicEmitter::Init() 
	{
		transform = GetEntity()->GetComponent<Transform>();

		if (transform == nullptr) 
		{
			Console::Output::PrintError("Missing transform", "The entity must contain a transform component.");
			this->active = false;
			return;
		}
	}

	void MusicEmitter::Start() 
	{
		if (playOnStart)
			Play();
	}
	
	void MusicEmitter::LoadMusic(CRefString fileName)
	{
		music = Resources::ResourcesManager::Instance()->AddMusic(fileName);

		music_id = music->GetMusicId();
	}

	void MusicEmitter::Play() 
	{
		if (emitterOnChannel != nullptr)
			emitterOnChannel->onChannel = false;

		emitterOnChannel = this;

		onChannel = true;

		sManager->SetMusicVolume(volume * MIX_MAX_VOLUME);

		sManager->PlayMusic(music_id, loop);
	}

	void MusicEmitter::Pause() 
	{
		if (onChannel)
			sManager->PauseMusic();
	}

	void MusicEmitter::Stop() 
	{
		if (onChannel) 
		{
			sManager->HaltMusic();
			onChannel = false;
		}
	}

	void MusicEmitter::Resume() 
	{
		if (onChannel)
			sManager->ResumeMusic();
	}

	void MusicEmitter::PlayWithFadeIn(float seconds, int loops) 
	{
		if (emitterOnChannel != nullptr)
			emitterOnChannel->onChannel = false;

		emitterOnChannel = this;
		
		onChannel = true;

		sManager->SetMusicVolume(volume * MIX_MAX_VOLUME);

		sManager->FadeInMusic(music_id, seconds * 1000.0f, loops);
	}

	void MusicEmitter::FadeOut(float seconds)
	{
		if (onChannel)
			sManager->FadeOutMusic(seconds * 1000.0f);
	}

	bool MusicEmitter::IsPlaying() 
	{
		if (onChannel)
			return sManager->IsMusicPlaying();

		return false;
	}

	bool MusicEmitter::IsPaused()
	{
		if (onChannel)
			return sManager->MusicPaused();

		return false;
	}

	void MusicEmitter::Rewind() 
	{
		if (onChannel)
			sManager->RewindMusic();
	}

	void MusicEmitter::SetVolume(float volume) 
	{
		if (volume < 0.0f || volume > 1.0f) 
		{
			Console::Output::PrintError("Invalid volume argument", "Volume value must be between 0 and 1!");
			return;
		}

		this->volume = volume;
	}
}
