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
        static vector<LogicObject*>dynamicObjects;
        static vector<LogicObject*>staticObjects;
        static void initialize(void*app);
        static void updateDynamicObject();
        static void startRender();
    };
}