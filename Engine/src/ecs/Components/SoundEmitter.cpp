#include "SoundEmitter.h"
#include "SoundEffect.h"
#include "Transform.h"
#include "Entity.h"

#include <ResourcesManager.h>
#include <RendererManager.h>
#include <ConsoleManager.h>
#include <SoundManager.h>
#include <cmath>

#define MIX_MAX_PANNING 255
#define MIX_AUDIBLE_DISTANCE 255

namespace ECS {

	std::vector<SoundEmitter*> SoundEmitter::soundEmitters{};

	SoundEmitter::SoundEmitter()
	{
		sManager = Sound::SoundManager::Instance();
		soundEmitters.push_back(this);
	}

	SoundEmitter::~SoundEmitter() 
	{
		Stop();
	}

	void SoundEmitter::Init() 
	{
		transform = GetEntity()->GetComponent<Transform>();

		if (transform == nullptr) 
		{
			Console::Output::PrintError("Missing transform", "The entity must contain a transform component.");
			this->active = false;;
			return;
		}

		float halfWidth = Renderer::RendererManager::Instance()->GetWidth() / 2.f;
		float haldHeight = Renderer::RendererManager::Instance()->GetHeight() / 2.f;

		audibleDistance = Utilities::Vector2D(halfWidth, haldHeight).Magnitude();
	}

	void SoundEmitter::Start() 
	{
		if (playOnStart)
			Play();
	}

	void SoundEmitter::Update(float deltaTime) 
	{
		if (onChannel && spatialSound) 
		{
			auto distanceToCamera = (transform->GetLocalPosition() - Renderer::RendererManager::Instance()->GetCameraPosition());

			auto dNormalized = distanceToCamera.Normalize();

			int16_t angle = atan2(dNormalized.GetX(), dNormalized.GetY()) * 180 / M_PI;

			int d = distanceToCamera.Magnitude() * MIX_AUDIBLE_DISTANCE / audibleDistance;

			if (d > MIX_AUDIBLE_DISTANCE) d = MIX_AUDIBLE_DISTANCE;

			sManager->SetChannelPosition(channel, angle, d);
		}
	}

	void SoundEmitter::LoadSound(CRefString fileName)
	{
		soundEffect = Resources::ResourcesManager::Instance()->AddSound(fileName);

		sound_id = soundEffect->GetSoundId();
	}

	void SoundEmitter::Play() 
	{
		onChannel = true;

		channel = sManager->PlaySound(sound_id, loop);

		sManager->SetChannelVolume(channel, volume * MIX_MAX_VOLUME);

		ApplyPanning();

		DisableEmittersOnSameChannel();
	}

	void SoundEmitter::PlayWithfadeIn(int seconds, int loops) 
	{
		onChannel = true;

		sManager->SetChannelVolume(channel, volume * MIX_MAX_VOLUME);

		channel = sManager->FadeInChannel(channel, sound_id, loops, seconds * 1000.0f);

		ApplyPanning();

		DisableEmittersOnSameChannel();
	}

	void SoundEmitter::Pause() 
	{
		if (onChannel)
			sManager->PauseChannel(channel);
	}

	void SoundEmitter::Stop() 
	{
		if (onChannel)
			sManager->StopChannel(channel);
	}

	void SoundEmitter::Resume() 
	{
		if (onChannel)
			sManager->ResumeChannel(channel);
	}

	void SoundEmitter::FadeOut(int seconds) 
	{
		if (onChannel)
			sManager->FadeOutChannel(channel, seconds * 1000.0f);
	}

	bool SoundEmitter::IsPlaying() 
	{
		if (onChannel)
			return sManager->IsChannelPlaying(channel);

		return false;
	}

	bool SoundEmitter::IsPaused() 
	{
		if (onChannel)
			return sManager->PausedChannel(channel);

		return false;
	}

	void SoundEmitter::SetVolume(float volume) 
	{
		if (volume < 0.0f || volume > 1.0f) 
		{
			Console::Output::PrintError("Invalid volume argument", "Volume value must be between 0 and 1!");
			return;
		}

		this->volume = volume;
	}

	void SoundEmitter::SetPanning(float panning) 
	{
		if (volume < 0.0f || volume > 1.0f) 
		{
			Console::Output::PrintError("Invalid volume argument", "Panning value must be between 0 and 1!");
			return;
		}

		this->panning = panning;

		if (onChannel)
			ApplyPanning();
	}

	void SoundEmitter::DisableEmittersOnSameChannel() 
	{
		for (const auto& s : soundEmitters)
			if (s != nullptr && s != this)
				if (s->onChannel && s->channel == channel)
					s->onChannel = false;
	}

	void SoundEmitter::ApplyPanning() 
	{
		if (!spatialSound)
			sManager->SetChannelPanning(channel, MIX_MAX_PANNING - (panning * MIX_MAX_PANNING), panning * MIX_MAX_PANNING);
	}

}
