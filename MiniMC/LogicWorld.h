#pragma once
#include"Vector3.h"
#include<vector>
#include "Object.h"
#include "Menu.h"

extern bool pp;//for pause of menu
namespace GameLogic {
    using std::vector;
    //it will be a single instance class in future.
    class WorldControler {
    private:
    public:
        static void* meshMap;
        static Menu* menu;

        static LogicObject* player;
        static bool onTheGround;
        static double playerForward[2];
        static Vector3 cameraOffset;

        static vector<LogicObject*>dynamicObjects;
        static vector<LogicObject*>staticObjects;
        static void initialize();
        static void startRender();
        static void updateCamera();
    };
}