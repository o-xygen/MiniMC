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
        int indexX, indexY, indexZ;
        Vector3 range[2];

        static GameLogic::Vector3 offset;
        static int mapLengthX, mapLengthY, mapLengthZ;
        static CubicRoom**** map;

        static void initialize(int x, int y, int z);
        friend class PhysicsFunction;
    };
}
