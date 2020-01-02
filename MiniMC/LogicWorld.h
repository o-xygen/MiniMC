#pragma once
#include"Vector3.h"
#include<vector>
#include "demoBlock.h"
#include "Object.h"
namespace GameLogic {
    using std::vector;
    //it will be a single instance class in future.
    class WorldControler {
    public:
        static double camera[3];
        static void* meshMap;
        static LogicObject* player;
        static Vector3 cameraOffset;
        static vector<LogicObject*>dynamicObjects;
        static vector<LogicObject*>staticObjects;
        static void initialize();
        static void updateDynamicObject();
        static void startRender();
    };
}