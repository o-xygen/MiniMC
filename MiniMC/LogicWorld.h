#pragma once
#include"Vector3.h"
#include<vector>
#include "demoBlock.h"
#include "Object.h"
namespace GameLogic {
    using std::vector;
    class WorldControler {
    public:
        static double camera[3];
        static LogicObject* player;
        static Vector3 cameraOffset;
        static vector<LogicObject*>objects;
        static void initialize();
        static void startRender();
    };
}