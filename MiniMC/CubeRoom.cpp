#include "CubeRoom.h"

namespace Physics
{

    int CubeRoom::x = 0, CubeRoom::y = 0, CubeRoom::z = 0;
    CubeRoom**** CubeRoom::map = nullptr;
    double CubeRoom::offset[3] = {};
    void CubeRoom::initialize(int x, int y, int z)
    {
        CubeRoom::x = x;
        CubeRoom::y = y;
        CubeRoom::z = z;
        map = new CubeRoom***[x];
        for (int i = 0; i < x; ++i)
        {
            map[i] = new CubeRoom**[y];
            for (int j = 0; j < y; ++j)
            {
                map[i][j] = new CubeRoom * [z];
                for (int k = 0; k < z; ++k)
                {
                    map[i][j][k] = new CubeRoom();
                }
            }
        }
    }
}
