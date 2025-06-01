#include "ParticleSystem.h"
#include <ResourcesManager.h>
#include <PhysicsManager.h>
#include <ConsoleManager.h>
#include "ETime.h"
#include "Transform.h"
#include "Particle.h"
#include "Entity.h"
#include "Texture.h"
#include <cassert>
#include <Random.h>

namespace ECS {

	// ------------------ BURST ----------------------

	Burst::Burst(ParticleSystem* system, float time, int particles, int cycles, float rate, float probability) 
	: system(system), timeToBurst(time), nParticles(particles), cycles(cycles), rate(rate), probability(probability) 
	{
		currentCycles = cycles;
	}

	void Burst::Reset() {
		burstTimer = 0;
		currentCycles = cycles;
		intervalTimer = 0;
	}

	// -------------- PARTICLE SYSTEM ----------------

	ParticleSystem::ParticleSystem() 
	{
		std::srand(std::time(nullptr));

		physicsManager = Physics::PhysicsManager::Instance();

		world = physicsManager->GetWorld();

		screenToWorldFactor = physicsManager->GetScreenToWorldFactor();
	}

	ParticleSystem::~ParticleSystem() 
	{
		CloseSystem();
	}

	void ParticleSystem::Init() 
	{
		tr = this->GetEntity()->GetComponent<Transform>();
		if (tr == nullptr) 
		{
			Console::Output::PrintError("Missing transform", "The entity must contain a transform component.");
			this->active = false;
			return;
		}

		for (int i = 0; i < maxParticles; i++)
			particles.push_back(new Particle(this, i));

		for (int i = maxParticles - 1; i >= 0; i--)
			particlesPool.push(i);
	}

	void ParticleSystem::Start() 
	{
		prevPosition = tr->GetLocalPosition();

		if (!fileName.empty())
			LoadTexture(fileName);  

		if (playOnStart)
			StartEmitting();
	}

	void ParticleSystem::Update(float deltaTime) 
	{
 		if (!emitting) return;

		timeSinceStart += deltaTime;

		// If the system is not emitting or the current time is smaller than delay to start time
		if (timeSinceStart < delay) return;

		currentTime += deltaTime;

		// If the time since the system started is greater than the system duration
		if (currentTime >= duration) 
		{
			Reset();
			return;
		}

		// Particle emission

			// Emission rate over distance
			if ((tr->GetLocalPosition() - prevPosition).Magnitude() > physicsManager->GetScreenToWorldFactor() / emissionRateOverDistance) 
			{
				prevPosition = tr->GetLocalPosition();

				TakeParticleFromPool();
			}

			// Emission rate over time
			timer += deltaTime;
			if (timer > 1.0f / emissionRateOverTime) 
			{
				timer = 0;

				TakeParticleFromPool();
			}

			// Bursts
			HandleBursts(deltaTime);
	}

	void ParticleSystem::FixedUpdate(float fixedDeltaTime) 
	{
		// Particles fixedupdate
		for (auto p : particles)
			p->FixedUpdate(fixedDeltaTime);

		// Particles remove
		HandleUnusedParticles();
	}

	void ParticleSystem::Render() 
	{
		// Particles render
		for (auto p : particles)
			p->Render();
	}

	void ParticleSystem::TakeParticleFromPool() 
	{
		if (particlesPool.empty()) return;

		int particleIdx = particlesPool.top();
		particlesPool.pop();

		particles[particleIdx]->SetAsUsed();

		nParticles++;
	}

	void ParticleSystem::ReturnParticleToPool(int idx) 
	{
		particles[idx]->SetAsUnused();

		particlesPool.push(idx);

		nParticles--;
	}

	void ParticleSystem::CloseSystem() 
	{
		for (auto b : bursts)
			delete b;

		bursts.clear();

		for (auto p : particles)
			delete p;

		particles.clear();

		unusedParticles.clear();
	}

	void ParticleSystem::HandleUnusedParticles() 
	{
		for (auto d : unusedParticles)
			ReturnParticleToPool(d->GetIdx());

		unusedParticles.clear();
	}

	void ParticleSystem::HandleBursts(float deltaTime) 
	{
		for (const auto& b : bursts) 
		{
			// If has already burst n cycles
			if (b->GetCycles() <= 0) continue;

			// If it is time to burst
			if (b->GetCurrentTime() > b->GetRate() && b->GetIntervalTime() <= 0)
			{
				// Calculate probability to burst
				float rnd = Utilities::Random::RandomBetween(0.0f, 1.0f);
				if (b->GetProbabilityToBurst() < rnd) continue;

				b->DecreaseCycles();
				b->SetIntervalTimer(b->GetTimeBetweenBursts());

				// Burst
				for (int i = 0; i < b->GetNumberOfParticles(); i++)
					TakeParticleFromPool();
			}

			// Timers
			b->SetBurstTimer(b->GetCurrentTime() + deltaTime);
			b->SetIntervalTimer(b->GetIntervalTime() - deltaTime);
		}
	}

	void ParticleSystem::Reset() 
	{
		for (const auto& p : particles) 
		{
			if (p->IsBeingUsed())
			{
				p->SetAsUnused();
				unusedParticles.push_back(p);
			}
		}

		HandleUnusedParticles();

		emitting = loop;
		currentTime = 0;
		timer = 0;

		// Reset bursts
		for (const auto& b : bursts)
			b->Reset();
	}

	void ParticleSystem::LoadTexture(CRefString texturePath)
	{
		fileName = texturePath;
		texture = Resources::ResourcesManager::Instance()->AddTexture(fileName);
		srcWidth = texture->GetWidth(); srcHeight = texture->GetHeight();
	}

	void ParticleSystem::AddBurst(float time, int particles, int cycles, float rate, float probability)
	{
		Burst* newBurst = new Burst(this, time, particles, cycles, rate, probability);
		bursts.push_back(newBurst);
	}
}
