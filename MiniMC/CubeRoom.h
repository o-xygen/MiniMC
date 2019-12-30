#pragma once
#include <vector>
#include "Vector3.h"
#include "Object.h"

namespace Physics
{
    using std::vector;
    using DataType::PhysicsComponent;
    class PhysicsFunction;
    class CubeRoom
    {
    public:
        static double offset[3];
        static int x, y, z;
        static CubeRoom**** map;

        vector<PhysicsComponent*> list{};

        static void initialize(int x, int y, int z);
        friend class PhysicsFunction;
    };
}
