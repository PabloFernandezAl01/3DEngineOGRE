#pragma once

#include <box2d/b2_fixture.h>
#include <ETypes.h>
#include <SDL_rect.h>

struct SDL_Renderer;
class b2BodyDef;
class b2Body;
class b2FixtureDef;
class b2Fixture;
class b2World;
class b2PolygonShape;

namespace ECS {

	class ParticleSystem;

	struct FloatColor {
		float r, g, b;
	};

	class Particle {

	public:

		Particle(ParticleSystem* system, int idx);

		~Particle();

		void FixedUpdate(float fixedDeltaTime);

		void Render();

		inline int GetIdx() { return idx; }

		void SetAsUnused();

		void SetAsUsed();

		inline bool IsBeingUsed() { return beingUsed; }

	private:

		void Init();

		void CalculateOverLifeTimeSettings();

		void CreatePhysicsAttributes();

		void RecreateFixture();

		ParticleSystem* system{};

		Utilities::Vector2D position;
		Utilities::Vector2D direction;
		Utilities::Vector2D size;
		Utilities::Color color{};

		float force{};
		float impulse{};
		float rotation{};
		float angularVelocity{};
		float linearDamping{};
		float angularDamping{};
		float bounciness{};
		float lifeTime{};
		float speed{};
		int alpha{};
		float timer{};

		// Start values
		Utilities::Vector2D startSize;
		Utilities::Vector2D endDirection;
		Utilities::Color startColor{};
		float startLifeTime{};
		float startSpeed{};
		int startAlpha{};

		int idx{};
		bool beingUsed{};

		// SDL Attributes
		SDL_Renderer* renderer{};
		SDL_Rect srcRect{};
		SDL_Rect dstRect{};
		SDL_Point rotationPoint{};

		// Box2D Attributes
		b2BodyDef* bodyDef{};
		b2Body* body{};
		b2FixtureDef* fixtureDef{};
		b2Fixture* fixture{};
		float mass{};
	};

}

