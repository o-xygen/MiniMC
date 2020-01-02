#include "CubicRoom.h"

namespace Physics
{

    int CubicRoom::x = 0, CubicRoom::y = 0, CubicRoom::z = 0;
    CubicRoom**** CubicRoom::map = nullptr;
    GameLogic::Vector3 CubicRoom::offset = {};
    void CubicRoom::initialize(int x, int y, int z)
    {
        CubicRoom::x = x;
        CubicRoom::y = y;
        CubicRoom::z = z;
        map = new CubicRoom***[x];
        for (int i = 0; i < x; ++i)
        {
            map[i] = new CubicRoom**[y];
            for (int j = 0; j < y; ++j)
            {
                map[i][j] = new CubicRoom * [z];
                for (int k = 0; k < z; ++k)
                {
                    map[i][j][k] = new CubicRoom();
                    map[i][j][k]->indexX = i;
                    map[i][j][k]->indexY = j;
                    map[i][j][k]->indexZ = k;
                }
            }
        }
    }
}
