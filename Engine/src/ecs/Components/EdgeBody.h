#pragma once

#include "PhysicBody.h"

// *** NOT UPDATED -> NO AVAILABLE TO USE ***

namespace ECS {

    class EdgeBody : public PhysicBody {

    public:

        EdgeBody() {};

        void Init() override;

        void SetEdgeVertices(const Vector2D& v1, const Vector2D& v2);

        inline float GetSize() { return size; }

    private:

        void SetMass(float mass) override {};

        float GetArea() override { return 0; };

        void ScaleShape() override;

        void SetBodyType(BODY_TYPE t) {};

        bool xAxis{};
        float size{};

        // Box2d circleShape
        b2EdgeShape* shape{};

        b2Vec2 vertex1{};
        b2Vec2 vertex2{};


    };

}

