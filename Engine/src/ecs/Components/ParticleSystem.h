#pragma once

#include "Component.h"
#include <ETypes.h>
#include <vector>
#include <stack>
#include <list>

namespace Renderer {
    class Texture;
}

namespace Physics {
    class PhysicsManager;
}

class b2World;

namespace ECS {

    class Transform;
    class Particle;
    class ParticleSystem;

    class Burst {

    public:

        Burst(ParticleSystem* system, float time, int particles, int cycles, float rate, float probability);

        void Reset();

        // Setters & getters
        inline float GetCurrentTime() { return burstTimer; }
        inline void SetBurstTimer(float time) { burstTimer = time; }

        inline float GetIntervalTime() { return intervalTimer; }
        inline void SetIntervalTimer(float time) { intervalTimer = time; }

        inline float GetRate() { return timeToBurst; }
        inline int GetNumberOfParticles() { return nParticles; }

        inline int GetCycles() { return currentCycles; }
        inline void DecreaseCycles() { currentCycles--; }

        inline float GetProbabilityToBurst() { return probability; }
        inline float GetTimeBetweenBursts() { return rate; }

    private:

        // Delay time to generate the burst
        float timeToBurst{};

        // Time between bursts
        float rate{};

        // Particles to be generated
        int nParticles{};

        // Times to generate the burst
        int cycles{};

        // Probability to burst
        float probability{};

        ParticleSystem* system{};

        float burstTimer{};
        float intervalTimer{};
        int currentCycles{};

    };

    class ParticleSystem : public Component {

        friend class Particle;
        friend class Burst;

    public:

        ParticleSystem();

        ~ParticleSystem();
        
        inline void StartEmitting() { emitting = true; }

        inline void StopEmitting() { emitting = false; }

        inline bool IsEmitting() { return emitting; }

        void LoadTexture(CRefString texturePath);

        void AddBurst(float time, int particles, int cycles, float rate, float probability);

        inline void SetDuration(float duration) { this->duration = duration; }

        inline void SetMaxParticles(float maxParticles) { this->maxParticles = maxParticles; }

        inline void SetLoop(bool loop) { this->loop = loop; }

        inline void SetDelay(float delay) { this->delay = delay; }

        inline void ShouldPlayOnStart(bool start) { playOnStart = start; }

    public:

		void Init() override;

		void Start() override;

		void Update(float deltaTime) override;

		void FixedUpdate(float fixedDeltaTime) override;

		void Render() override;

		// Private methods
		void TakeParticleFromPool();
		void ReturnParticleToPool(int idx);
		void HandleUnusedParticles();
		void HandleBursts(float deltaTime);
		void CloseSystem();
		void Reset();

        // General system configuration
        float duration{};
        int maxParticles{};
        bool loop{};
        float delay{};
        bool playOnStart{};

        // Particles START configuration

            // Lifetime
            float lifeTime{};
            bool randomLifeTimeBetweenTwoValues{};
            float lifeTimeFirstValue{};
            float lifeTimeSecondValue{};

            // Speed
            float speed{};
            bool randomSpeedBetweenTwoValues{};
            float speedFirstValue{};
            float speedSecondValue{};

            // Size
            Utilities::Vector2D size{};
            bool randomSizeBetweenTwoValues{};
            Utilities::Vector2D sizeFirstValue{};
            Utilities::Vector2D sizeSecondValue{};

            // Angle
            float angle{};
            bool randomAngleBetweenTwoValues{};
            float angleFirstValue{};
            float angleSecondValue{};

            // Position
            Utilities::Vector2D spawnPosition{};
            Utilities::Vector2D position{};
            bool randomPositionBetweenTwoValues{};
            Utilities::Vector2D positionFirstValue{};
            Utilities::Vector2D positionSecondValue{};
        
            // Rotation
            float rotation{};
            bool randomRotationBetweenTwoValues{};
            float rotationFirstValue{};
            float rotationSecondValue{};

            // Color
            Utilities::Color color{};
            bool randomColorBetweenTwoColors{};
            Utilities::Color colorFirstValue{};
            Utilities::Color colorSecondValue{};


        // Physics particles configuration
        std::string layerName;
        bool sensor{};
        float gravityScale{};

            // Mass
            float mass{};
			bool randomMassBetweenTwoValues{};
			float massFirstValue{};
			float massSecondValue{};

            // Force
            float force{};
            bool randomForceBetweenTwoValues{};
            float forceFirstValue{};
            float forceSecondValue{};

            // Impulse
            float impulse{};
            bool randomImpulseBetweenTwoValues{};
            float impulseFirstValue{};
            float impulseSecondValue{};

            // Angular velocity
            float angularVelocity{};
            bool randomAngularVelocityBetweenTwoValues{};
            float angularVelocityFirstValue{};
            float angularVelocitySecondValue{};

            // Linear damping
            float linearDamping{};
			bool randomLinearDampingBetweenTwoValues{};
			float linearDampingFirstValue{};
			float linearDampingSecondValue{};

			// Angular damping
			float angularDamping{};
			bool randomAngularDampingBetweenTwoValues{};
			float angularDampingFirstValue{};
			float angularDampingSecondValue{};

            // Bounciness
            float bounciness{};
            bool randomBouncinessBetweenTwoValues{};
            float bouncinessFirstValue{};
            float bouncinessSecondValue{};

			// Alpha
			int alpha{};
			bool randomAlphaBetweenTwoValues{};
			int alphaFirstValue{};
			int alphaSecondValue{};

			// Emission coniguration
			float emissionRateOverTime{};
			float emissionRateOverDistance{};

			// End lifetime configuration
			bool overLifeTimeSpeed{};
			float endSpeed{};

			bool overLifeTimeColor{};
			Utilities::Color endColor{};

			bool overLifeTimeSize{};
			Utilities::Vector2D endSize{};

			bool overLifeTimeAlpha{};
			int endAlpha{};

        // Render configuration
        std::string fileName{};
        int flipmode{};
        int srcX{};
        int srcY{};
        int srcWidth{};
        int srcHeight{};

        // Private attributes
        bool emitting{};
        float currentTime{};
        float timeSinceStart{};
        float timer{};
        int nParticles{};

        Transform* tr{};
        Physics::PhysicsManager* physicsManager{};
        float screenToWorldFactor{};

        Utilities::Vector2D prevPosition{};
        Renderer::Texture* texture{};

        // Bursts
        std::vector<Burst*> bursts{};

        // Particles pool
        std::stack<int> particlesPool{};
        std::vector<Particle*> particles{};
        std::list<Particle*> unusedParticles{};

        // Box2D
        b2World* world{};

    };

}

