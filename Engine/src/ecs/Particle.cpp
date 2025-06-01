#include "Particle.h"
#include "RendererManager.h"
#include "PhysicsManager.h"
#include "box2d/box2d.h"
#include "SDL_render.h"
#include "Components/ParticleSystem.h"
#include "Components/Transform.h"
#include "Texture.h"
#include "Random.h"

using namespace Utilities;

namespace ECS {

	Particle::Particle(ParticleSystem* system, int idx) : system(system), idx(idx)
	{
		renderer = Renderer::RendererManager::Instance()->GetRenderer();

		CreatePhysicsAttributes();
	}

	Particle::~Particle()
	{
		delete bodyDef;
		delete fixtureDef;
	}

	void Particle::FixedUpdate(float fixedDeltaTime)
	{
		if (!beingUsed) return;

		timer += fixedDeltaTime;
		lifeTime -= fixedDeltaTime;

		// Over Life Time Settings
		CalculateOverLifeTimeSettings();

		if (lifeTime <= 0)
			system->unusedParticles.push_back(this);
		
		if (system->gravityScale == 0)
			body->SetLinearVelocity({ direction.GetX() * speed * fixedDeltaTime, direction.GetY() * speed * fixedDeltaTime });

		// Position
		position = { body->GetPosition().x * system->screenToWorldFactor, body->GetPosition().y * system->screenToWorldFactor };

		// Rotation
		rotation = body->GetAngle() * (180 / b2_pi);

	}

	void Particle::Render() 
	{
		if (!beingUsed) return;

		srcRect = { system->srcX, system->srcX, system->srcWidth, system->srcHeight };

		int w = size.GetX();
		int h = size.GetY();
		int x = std::round(position.GetX() - w * 0.5f);
		int y = std::round(position.GetY() + h * 0.5f);

		Renderer::RendererManager::Instance()->AdjustRectToCamera(&x, &y, &w, &h, {1, 1});

		dstRect = { x, y, w, h };

		rotationPoint.x = w / 2;
		rotationPoint.y = h / 2;

		auto texture = system->texture->GetSDLTexture();

		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
		SDL_SetTextureAlphaMod(texture, alpha);
		SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, rotation, &rotationPoint, (SDL_RendererFlip) system->flipmode);
	}

	void Particle::SetAsUnused() 
	{
		beingUsed = false;

		body->SetLinearVelocity({ 0,0 });
		body->SetAngularVelocity(0);
		body->SetEnabled(false);
	}

	void Particle::SetAsUsed() 
	{
		beingUsed = true;

		Init();
	}

	void Particle::Init() 
	{
		float factor = system->screenToWorldFactor;

		// Timer
		timer = 0.0f;


		// Position
		position = system->tr->GetWorldPosition() + system->position + system->spawnPosition;
		if (system->randomPositionBetweenTwoValues)
			position = system->tr->GetWorldPosition() + system->spawnPosition + Random::RandomVectorBetween(system->positionFirstValue, system->positionSecondValue);


		// LifeTime
		lifeTime = system->lifeTime;
		if (system->randomLifeTimeBetweenTwoValues)
			lifeTime = Random::RandomBetween(system->lifeTimeFirstValue, system->lifeTimeSecondValue);

		startLifeTime = lifeTime;


		// Speed
		speed = system->speed;
		if (system->randomSpeedBetweenTwoValues)
			speed = Random::RandomBetween(system->speedFirstValue, system->speedSecondValue);

		startSpeed = speed;


		// Size
		size = system->size;
		if (system->randomSizeBetweenTwoValues) {
			float x = Random::RandomBetween(system->sizeFirstValue.GetX(), system->sizeSecondValue.GetX());
			float y = Random::RandomBetween(system->sizeFirstValue.GetY(), system->sizeSecondValue.GetY());

			size = { x, y };
		}

		startSize = size;

		// Mass
		mass = system->mass;
		if (system->randomMassBetweenTwoValues)
			mass = Random::RandomBetween(system->massFirstValue, system->massSecondValue);

		// Force
		force = system->force;
		if (system->randomForceBetweenTwoValues)
			force = Random::RandomBetween(system->forceFirstValue, system->forceSecondValue);


		// Impulse
		impulse = system->impulse;
		if (system->randomImpulseBetweenTwoValues)
			impulse = Random::RandomBetween(system->impulseFirstValue, system->impulseSecondValue);


		// Direction
		float angle = system->angle;
		if (system->randomAngleBetweenTwoValues)
			angle = Random::RandomBetween(system->angleFirstValue, system->angleSecondValue);

		float radians = angle * b2_pi / 180.0f;
		direction = { cos(radians), sin(radians) };

		// Rotation
		rotation = system->rotation;
		if (system->randomRotationBetweenTwoValues)
			rotation = Random::RandomBetween(system->rotationFirstValue, system->rotationSecondValue);

		// Angular Velocity
		angularVelocity = system->angularVelocity;
		if (system->randomAngularVelocityBetweenTwoValues)
			angularVelocity = Random::RandomBetween(system->angularVelocityFirstValue, system->angularVelocitySecondValue);

		// Linear damping
		linearDamping = system->linearDamping;
		if (system->randomLinearDampingBetweenTwoValues)
			linearDamping = Random::RandomBetween(system->linearDampingFirstValue, system->linearDampingSecondValue);

		// Angular damping
		angularDamping = system->angularDamping;
		if (system->randomAngularDampingBetweenTwoValues)
			angularDamping = Random::RandomBetween(system->angularDampingFirstValue, system->angularDampingSecondValue);

		// Color
		color = system->color;
		if (system->randomColorBetweenTwoColors)
			color = Random::RandomColorBetween(system->colorFirstValue, system->colorSecondValue);

		startColor = color;

		// Alpha
		alpha = system->alpha;
		if (system->randomAlphaBetweenTwoValues)
			alpha = Random::RandomIntBetween(system->alphaFirstValue, system->alphaSecondValue);

		startAlpha = alpha;

		// Bounciness
		bounciness = system->bounciness;
		if (system->randomBouncinessBetweenTwoValues)
			bounciness = Random::RandomBetween(system->bouncinessFirstValue, system->bouncinessSecondValue);

		
		// Physics
		RecreateFixture();

		body->SetEnabled(true);

		body->SetGravityScale(system->gravityScale);

		body->SetTransform({ position.GetX() / factor, position.GetY() / factor }, rotation * (b2_pi / 180));

		fixture->SetSensor(system->sensor);

		fixture->SetRestitution(bounciness);

		body->SetAngularVelocity(angularVelocity);

		body->SetLinearDamping(linearDamping);

		body->SetAngularDamping(angularDamping);

		body->ApplyLinearImpulseToCenter({ impulse * direction.GetX(), impulse * direction.GetY()}, true);

		/*body->ApplyForceToCenter({ force * direction.GetX(), force * direction.GetY() }, true);*/
	}

	void Particle::CalculateOverLifeTimeSettings() 
	{
		float lifePercentage = timer / startLifeTime;

		// Speed
		if (system->overLifeTimeSpeed) 
			speed = lifePercentage * (system->endSpeed - startSpeed) + startSpeed;

		// Color
		if (system->overLifeTimeColor)
		{
			color.r = std::lerp(startColor.r, system->endColor.r * 255, lifePercentage);
			color.g = std::lerp(startColor.g, system->endColor.g * 255, lifePercentage);
			color.b = std::lerp(startColor.b, system->endColor.b * 255, lifePercentage);
		}

		// Size 
		if (system->overLifeTimeSize) {
			size = (system->endSize - startSize) * lifePercentage + startSize;
			RecreateFixture();
		}

		// Alpha
		if (system->overLifeTimeAlpha)
			alpha = lifePercentage * (system->endAlpha - startAlpha) + startAlpha;
	}

	void Particle::CreatePhysicsAttributes() 
	{
		// Physics Attributes creation
		bodyDef = new b2BodyDef();
		fixtureDef = new b2FixtureDef();
		b2PolygonShape shape{};

		size = { 100, 100 };
		shape.SetAsBox(size.GetX() / 2.f / system->screenToWorldFactor, size.GetY() / 2.f / system->screenToWorldFactor);
		bodyDef->type = b2_dynamicBody;
		bodyDef->position.Set(0, 0);
		bodyDef->userData.pointer = uintptr_t(static_cast<void*>(nullptr));

		fixtureDef->shape = &shape;
		fixtureDef->density = 1.0f;
		fixtureDef->isSensor = false;

		body = system->world->CreateBody(bodyDef);
		fixture = body->CreateFixture(fixtureDef);

		// Collision Filtering
		b2Filter filter = fixture->GetFilterData();

		filter.categoryBits = system->physicsManager->GetLayerBits(system->layerName);
		filter.maskBits = system->physicsManager->GetMaskBits(system->layerName);

		fixture->SetFilterData(filter);

		body->SetEnabled(false);
	}

	void Particle::RecreateFixture()
	{
		Vector2D sizeWorldUnits = size / system->screenToWorldFactor;

		body->DestroyFixture(fixture);
		b2PolygonShape newShape{};

		newShape.SetAsBox(sizeWorldUnits.GetX() / 2.f, sizeWorldUnits.GetY() / 2.f);

		fixtureDef->shape = &newShape;
		fixtureDef->density = mass / (sizeWorldUnits.GetX() * sizeWorldUnits.GetY());
		fixtureDef->isSensor = false;

		fixture = body->CreateFixture(fixtureDef);

		// Collision Filtering
		b2Filter filter = fixture->GetFilterData();

		filter.categoryBits = system->physicsManager->GetLayerBits(system->layerName);
		filter.maskBits = system->physicsManager->GetMaskBits(system->layerName);

		fixture->SetFilterData(filter);

		body->ResetMassData();
	}
}
