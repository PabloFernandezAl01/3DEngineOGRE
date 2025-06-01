#pragma once

#include "Component.h"
#include <box2d/b2_fixture.h>
#include <ETypes.h>
#include <RaycastData.h>

class b2BodyDef;
class b2Body;
class b2FixtureDef;
class b2World;
class b2Shape;
enum b2BodyType;

using namespace Utilities;
using namespace Physics;

namespace Physics {
    class PhysicsManager;
}

namespace ECS {

    class Transform;

    class PhysicBody : public Component {

    public:

        enum class BODY_TYPE { STATIC = 0, KINEMATIC = 1, DYNAMIC = 2 };

        PhysicBody();

        ~PhysicBody();

        void Init() override;

        void Start() override;

        void OnDestroy() override;

        void FixedUpdate(float fixedDeltaTime) override;

        void OnActive() override;

        void OnDeacitve() override;

        void OnSceneUp() override;

        void OnSceneDown() override;

        // Setters & getters
        inline void SetTrigger(bool trigger) { fixture->SetSensor(trigger); }
        inline bool IsTrigger() { return fixture->IsSensor(); }

        inline void SetFriction(float friction) { fixture->SetFriction(friction); }
        inline float GetFriction() { return fixture->GetFriction(); }

        inline void SetBounciness(float bounciness) { fixture->SetRestitution(bounciness); }
        inline float GetBounciness() { return fixture->GetRestitution(); }

        inline CRefVector2 GetOffSet() { return offSet; }
        inline void AddOffSet(float x, float y) { offSet.Set(offSet.GetX() + x, offSet.GetY() + y); }

        inline void SetRotationFreezed(bool freezed) { body->SetFixedRotation(freezed); }
        inline bool IsRotationFreezed() { return body->IsFixedRotation(); }

        void SetBodyType(const BODY_TYPE& type);
        inline const BODY_TYPE& GetBodyType() { return bodyType; }

        inline void SetAsBullet(bool bullet) { body->SetBullet(bullet); }

        inline void SetLinearDrag(float drag) { body->SetLinearDamping(drag); }
        inline float GetLinearDrag() { return body->GetLinearDamping(); }

        inline void SetAngularDrag(float drag) { body->SetAngularDamping(drag); }
        inline float GetAngularDrag() { return body->GetAngularDamping(); }

        inline void SetGravityScale(float scale) { body->SetGravityScale(scale); }
        inline float GetGravityScale() { return body->GetGravityScale(); }

        // Collision Manifold properties
        inline CRefVector2 GetCollisionNormal() { return collisionNormal; }

        inline CRefVector2 GetCollisionPoint() { return collisionPoint; }

        inline Vector2D GetPositionWorldUnits() { return {body->GetPosition().x, body->GetPosition().y}; }

        inline Vector2D GetPositionPixelUnits() { return {body->GetPosition().x * screenToWorldFactor, body->GetPosition().y * screenToWorldFactor}; }

        // Collision Filtering
        void SetCollisionLayer(CRefString layerName);
        inline CRefString GetCollisionLayer() { return this->layerName; }

        void SetLinearVelocity(float x, float y) { body->SetLinearVelocity({ x, y }); }
        Vector2D GetLinearVelocity() { return { body->GetLinearVelocity().x, body->GetLinearVelocity().y }; }

        void SetAngularVelocity(float a) { body->SetAngularVelocity(a); }
        float GetAngularVelocity() { return body->GetAngularVelocity(); }

        // Force methods
        void ApplyForce(CRefVector2 force, CRefVector2 point);

        void ApplyForceToCenter(CRefVector2 force);

        void ApplyTorque(float torque);

        void ApplyLinearImpulse(CRefVector2 impulse, CRefVector2 point);

        void ApplyLinearImpulseToCenter(CRefVector2 impulse);

        void ApplyAngularImpulse(float impulse);

        // Raycasting
        bool Raycast(const RayCastInput& input, RayCastOutput* output, int childIndex);

    public:

        virtual void SetMass(float mass) = 0;
        inline float GetMass() { return mass; }
        
        virtual float GetArea() = 0;
        inline float GetAngle() { return body->GetAngle() * (180 / b2_pi); }
        
        // Collison/Trigger Stay
        void SetCollisionStay(bool stay, Entity* b);
        void SetTriggerStay(bool stay, Entity* b);

        void SetBox2DContact(b2Contact* c);

        bool CollidesWith(PhysicBody* b) const;

        static PhysicBody* GetComponentFromEntity(Entity* ent);

    protected:

        virtual void ScaleShape() = 0;

        // Box2d
        b2World* world{};
        PhysicsManager* pm{};
        float screenToWorldFactor{};
        Transform* transform{};

        Vector2D offSet;
        BODY_TYPE bodyType{};

        // Fixture properties
        float mass{1.f};
        float bounciness{};
        bool trigger{};
        bool freezeRotation{};
        float gravityScale{ 1.f };
        float friction{};
        float linearDamping{};
        float angularDamping{};

        // Collision Layer
        std::string layerName;

        // Box2d properties
        b2BodyDef* bodyDef{};
        b2Body* body{};
        b2FixtureDef* fixtureDef{};
        b2Fixture* fixture{};
        b2Contact* contact{};

        // Contact manifold properties
        Vector2D collisionNormal;
        Vector2D collisionPoint;

    private:

        Vector2D lastPositionSync;
        float lastRotationSync{};
        Vector2D lastScaleInfo;

        // Collison/Trigger Stay
        bool onCollisonStay{};
        bool onTriggerStay{};

        Entity* collisionEntity{};

    };

}

