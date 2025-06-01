#pragma once

#include "ETypes.h"
#include "PhysicBody.h"

namespace ECS {

    class BoxBody : public PhysicBody {

    public:

        BoxBody() {};

        void Init() override;

        inline CRefVector2 GetSize() { return size; }
        void SetSize(CRefVector2 size);

        void SetMass(float mass) override;

        inline float GetArea() override { return size.Area(); }

    private:

        void ScaleShape() override;

        Vector2D size;

        void RecreateFixture();

    };

}

