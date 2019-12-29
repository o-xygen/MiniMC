#pragma once
#include <vector>
#include "Vector3.h"

namespace Physics
{
    using std::vector;
    class PhysicsCube;
    class PhysicsUnit
    {
    public:
        Vector3 position;
        Vector3 velocity;
        PhysicsCube* parent;
        enum CubePhysicsType
        {
            RigidBody, NonRigidBody
        }isRigid;
        void* logicObject;

    };
    class PhysicsFunction;
    class PhysicsCube
    {
    public:
        static double offset[3];
        static int x, y, z;
        static PhysicsCube**** map;

        vector<PhysicsUnit*> list{};
        PhysicsUnit* terrainObject = nullptr;

        static void initialize(int x, int y, int z);
        friend class PhysicsFunction;
    };
}
