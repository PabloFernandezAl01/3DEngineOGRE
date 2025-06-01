#pragma once

#include "PhysicBody.h"

namespace ECS {

    class CircleBody : public PhysicBody {

    public:

        CircleBody() {};

        void Init() override;

        void SetRadius(float radius);
        inline float GetRadius() { return radius; }

        void SetMass(float mass) override;

        inline float GetArea() override { return b2_pi * std::pow(radius, 2); }

    private:

        void ScaleShape() override;

        void RecreateFixture();

        float radius{};
    };

}

