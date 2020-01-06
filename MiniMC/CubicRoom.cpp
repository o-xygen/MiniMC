#include "CubicRoom.h"

namespace Physics
{

    int CubicRoom::mapLengthX = 0, CubicRoom::mapLengthY = 0, CubicRoom::mapLengthZ = 0;
    CubicRoom**** CubicRoom::map = nullptr;
    GameLogic::Vector3 CubicRoom::offset = {};
    void CubicRoom::initialize(int x, int y, int z)
    {
        CubicRoom::mapLengthX = x;
        CubicRoom::mapLengthY = y;
        CubicRoom::mapLengthZ = z;
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
                    map[i][j][k]->range[0] = Vector3{ i + 0.,j + 0.,k + 0. } + offset;
                    map[i][j][k]->range[1] = Vector3{ i + 1.,j + 1.,k + 1. } + offset;
                }
            }
        }
    }
}
