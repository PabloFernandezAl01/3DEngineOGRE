#include "PhysicsManager.h"
#include "box2d/b2_contact.h"
#include "RaycastData.h"
#include "box2d/box2d.h"
#include "DebugDraw.h"

#include <ConsoleManager.h>
#include <iostream>

const int MAX_COLLISION_LAYERS = 16;

namespace Physics {

	PhysicsManager::PhysicsManager(const ConfigData& data, int velocityIterations, int positionIterations) 
	{
		this->gravity = new b2Vec2(data.gravity.GetX(), data.gravity.GetY());
		world = new b2World(*this->gravity);

		this->screenToWorldFactor = 100.0f;

		this->velocityIterations = velocityIterations;
		this->positionIterations = positionIterations;

		// Debug Draw
		debugDrawEnabled = false;

		b2draw = new DebugDraw();
		world->SetDebugDraw(b2draw);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_centerOfMassBit;
		b2draw->SetFlags(flags);

		// Collision Matrix
		layersCount = 0;

		collision_matrix = std::vector<std::vector<bool>>(MAX_COLLISION_LAYERS, std::vector<bool>(MAX_COLLISION_LAYERS, false));

		freeLayers = std::stack<int>();

		for (int i = MAX_COLLISION_LAYERS - 1; i >= 0; i--) freeLayers.push(i);

		LoadMatrixFromData(data.layers, data.collisionMatrix);
	}

	PhysicsManager::~PhysicsManager()
	{
		HandleBodies();

		delete gravity;
		delete world;
		delete b2draw;
	}

	void PhysicsManager::ShowMatrix()
	{
		for (int i = 0; i < layersCount; i++) 
		{
			for (int c = 0; c < layersCount; c++)
				std::cout << collision_matrix[i][c] << " ";

			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}

	void PhysicsManager::LoadMatrixFromData(std::vector<std::string> dataLayers, std::vector<std::vector<bool>> dataMatrix)
	{
		for (auto& l : dataLayers)
			AddCollisionLayer(l);

		for (int i = 0; i < dataLayers.size(); i++)
		{
			for (int c = 0; c < dataLayers.size(); c++)
			{
				SetCollisionBetweenLayers(dataLayers[i], dataLayers[dataLayers.size() - 1 - c], dataMatrix[i][c]);
			}
		}

	}

	void PhysicsManager::SetBodyEnabled(b2Body* body, bool enabled)
	{
		if (enabled)
			enabledBodies.push_back(body);
		else
			disabledBodies.push_back(body);
	}

	void PhysicsManager::HandleBodies() 
	{
		for (auto & disabledBodie : disabledBodies) 
			disabledBodie->SetEnabled(false);

		disabledBodies.clear();

		for (auto & enabledBodie : enabledBodies) 
			enabledBodie->SetEnabled(true);

		enabledBodies.clear();
	}

	void PhysicsManager::AddCollisionLayer(CRefString layerName) 
	{
		// Check if the maximun number of physics layers was reached
		if (layersCount >= MAX_COLLISION_LAYERS) 
		{
			Console::Output::PrintError("Physics layers", "Maximum number of layers reached.");
			return;
		}

		// Check if there is already an exisiting layer with the same name
		if (layers.find(layerName) != layers.end())
		{
			Console::Output::PrintError("Physics layers", "There is already a layer with the same name. Layers must be unique.");
			return;
		}

		layers.insert(std::make_pair(layerName, freeLayers.top()));

		freeLayers.pop();

		layersCount++;
	}

	int PhysicsManager::GetMaskBits(CRefString layerName) 
	{
		if (!LayersExists(layerName))
		{
			Console::Output::PrintError("Physics layers", "The layer with name " + layerName + " doesn't exist.");
			return 0;
		}

		int layerN = layers.at(layerName);

		int flags = 0;

		for (int i = 0; i < layersCount; i++) 
		{
			if (collision_matrix[layerN][layersCount - 1 - i])
				flags += std::pow(2, i);
		}

		return flags;
	}

	int PhysicsManager::GetLayerBits(CRefString layerName) 
	{
		if (!LayersExists(layerName))
		{
			Console::Output::PrintError("Physics layers", "The layer with name " + layerName + " doesn't exist.");
			return 0;
		}

		return std::pow(2, layers.at(layerName));
	}

	void PhysicsManager::SetCollisionBetweenLayers(CRefString layerNameA, CRefString layerNameB, bool collide)
	{
		if (!LayersExists(layerNameA)) 
		{
			Console::Output::PrintError("Physics layers", "The layer with name " + layerNameA + " doesn't exist.");
			return;
		}

		if (!LayersExists(layerNameB))
		{
			Console::Output::PrintError("Physics layers", "The layer with name " + layerNameB + " doesn't exist.");
			return;
		}

		int layerA = layers.at(layerNameA);
		int layerB = layers.at(layerNameB);

		collision_matrix[layerA][layersCount - 1 - layerB] = collide;
		collision_matrix[layerB][layersCount - 1 - layerA] = collide;
	}

	bool PhysicsManager::LayersCollide(CRefString layerNameA, CRefString layerNameB)
	{
		if (!LayersExists(layerNameA)) 
		{
			Console::Output::PrintError("Physics layers", "The layer with name " + layerNameA + " doesn't exist.");
			return false;
		}

		if (!LayersExists(layerNameB)) 
		{
			Console::Output::PrintError("Physics layers", "The layer with name " + layerNameB + " doesn't exist.");
			return false;
		}

		int layerA = layers.at(layerNameA);
		int layerB = layers.at(layerNameB);

		return collision_matrix[layerA][layersCount - 1 - layerB];
	}

	bool PhysicsManager::LayersExists(CRefString layerName) 
	{
		return layers.find(layerName) != layers.end();
	}

	bool PhysicsManager::RayCast(RayCastClosestCallback* callback, CRefVector2 p1, CRefVector2 p2)
	{
		world->RayCast(callback, { p1.GetX(), p1.GetY()}, { p2.GetX(), p2.GetY() });

		return callback->hit;
	}

	void PhysicsManager::SetContactListener(b2ContactListener* contactListener)
	{
		world->SetContactListener(contactListener);
	}

	void PhysicsManager::FixedUpdate(float fixedDeltaTime) 
	{
		world->Step(fixedDeltaTime, velocityIterations, positionIterations);
	}

	void PhysicsManager::debugDraw() 
	{
		if (debugDrawEnabled)
			 world->DebugDraw();
	}

	void PhysicsManager::EnableDebugDraw(bool enable) 
	{
		debugDrawEnabled = enable;
	}

	float PhysicsManager::GetScreenToWorldFactor()
	{
		return screenToWorldFactor;
	}

	b2World* PhysicsManager::GetWorld()
	{
		return world;
	}

	void PhysicsManager::SetGravity(cVector2D g)
	{
		gravity->Set(g.GetX(), g.GetY());
		world->SetGravity(*gravity);
	}

	Utilities::Vector2D PhysicsManager::GetGravity()
	{
		return {gravity->x, gravity->y};
	}

}
