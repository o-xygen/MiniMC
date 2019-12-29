#include "PhysicsCube.h"

namespace Physics
{

    int PhysicsCube::x = 0, PhysicsCube::y = 0, PhysicsCube::z = 0;
    PhysicsCube**** PhysicsCube::map = nullptr;
    double PhysicsCube::offset[3] = {};
    void PhysicsCube::initialize(int x, int y, int z)
    {
        PhysicsCube::x = x;
        PhysicsCube::y = y;
        PhysicsCube::z = z;
        map = new PhysicsCube * **[x];
        for (int i = 0; i < x; ++i)
        {
            map[i] = new PhysicsCube * *[y];
            for (int j = 0; j < y; ++j)
            {
                map[i][j] = new PhysicsCube * [z];
                for (int k = 0; k < z; ++k)
                {
                    map[i][j][k] = new PhysicsCube();
                }
            }
        }
    }
}
