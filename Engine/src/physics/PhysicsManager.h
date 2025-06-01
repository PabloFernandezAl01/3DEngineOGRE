#pragma once

#include <ConfigManager.h>
#include <unordered_map>
#include <Singleton.h>
#include <ETypes.h>
#include <vector>
#include <stack>

class b2Vec2;
class b2World;
class b2Body;
class b2ContactListener;

namespace Physics {

	class DebugDraw;
	class RayCastClosestCallback;

	class PhysicsManager : public Utilities::Singleton<PhysicsManager> {

		friend Singleton<PhysicsManager>;

	public:

		~PhysicsManager();

		b2World* GetWorld();

		void FixedUpdate(float fixedDeltaTime);

		void debugDraw();

		void EnableDebugDraw(bool enable);
		inline bool IsDebugDrawEnabled() { return debugDrawEnabled; }

		void HandleBodies();

		void SetContactListener(b2ContactListener* contactListener);

		float GetScreenToWorldFactor();

		int GetLayerBits(CRefString layerName);

		int GetMaskBits(CRefString layerName);

		void SetBodyEnabled(b2Body* body, bool enabled);

		Utilities::Vector2D GetGravity();

		void SetGravity(cVector2D gravity);

		void AddCollisionLayer(CRefString layerName);

		void SetCollisionBetweenLayers(CRefString layerNameA, CRefString layerNameB, bool collide);

		bool LayersCollide(CRefString layerNameA, CRefString layerNameB);

		bool LayersExists(CRefString layerName);

		bool RayCast(RayCastClosestCallback* callback, CRefVector2 p1, CRefVector2 p2);

	private:
		
		void ShowMatrix();

		PhysicsManager() {};

		PhysicsManager(const ConfigData& data, int velocityIterations = 6, int positionIterations = 3);

		void LoadMatrixFromData(std::vector<std::string> dataLayers, std::vector<std::vector<bool>> dataMatrix);

		int velocityIterations{ 6 };
		int positionIterations{ 3 };

		b2Vec2* gravity{};
		b2World* world{};

		bool debugDrawEnabled{};

		// Disabled/Enable bodies handling
		std::vector<b2Body*> disabledBodies;
		std::vector<b2Body*> enabledBodies;

		// Debug draw class inherited from b2draw
		DebugDraw* b2draw{};

		float screenToWorldFactor{};

		// Collision Matrix
		std::vector<std::vector<bool>> collision_matrix;

		std::unordered_map<std::string, int> layers;

		std::stack<int> freeLayers;

		int layersCount{};

	};
}
