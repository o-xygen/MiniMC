#pragma once
#include <vector>
#include "Vector3.h"
#include "Object.h"
#include "PhysicsFunction.h"

namespace Physics
{
    using std::vector;
    using GameLogic::PhysicsComponent;
    class CubicRoom
    {
    public:
        vector<PhysicsComponent*> list{};

        static GameLogic::Vector3 offset;
        static int x, y, z;
        static CubicRoom**** map;

        static void initialize(int x, int y, int z);
        friend class PhysicsFunction;
    };
}
