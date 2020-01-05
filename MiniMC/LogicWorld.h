#pragma once
#include"Vector3.h"
#include<vector>
#include "Object.h"
namespace GameLogic {
    using std::vector;
    //it will be a single instance class in future.
    class WorldControler {
    private:
        static void updateCamera();
    public:
        static void* meshMap;

        static LogicObject* player;
        static bool onTheGround;
        static double playerForward[2];
        static Vector3 cameraOffset;

        static vector<LogicObject*>dynamicObjects;
        static vector<LogicObject*>staticObjects;
        static void initialize();
        static void startRender();
    };
}