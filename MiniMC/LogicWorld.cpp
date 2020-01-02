#include "LogicWorld.h"
#include "CubicRoom.h"
#include "GlobalVariable.h"
#include <ctime>
#include "Application.h"
namespace GameLogic {
    double WorldControler::camera[3];
    LogicObject* WorldControler::player;
    Vector3 WorldControler::cameraOffset;
    vector<LogicObject*>WorldControler::dynamicObjects;
    vector<LogicObject*>WorldControler::staticObjects;
    void WorldControler::initialize(void*app) {
        Physics::CubicRoom::initialize(200, 20, 200);
        Physics::CubicRoom::offset = { -100, 0, -100 };

        ((Application*)app)->initBlockMap();
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                LogicObject* logicObject = new LogicObject();
                logicObject->setPosition(i - 100.0, 0.0, j - 100.0);
                logicObject->physicsObject->isRigid = true;
                logicObject->physicsObject->isTerrain = true;
                staticObjects.push_back(logicObject);
            }
        }
        player = new LogicObject();
        player->setPosition(0.0, 1.0, 0.0);
        player->physicsObject->isRigid = true;
        player->physicsObject->isTerrain = false;

        cameraOffset = { 0,0.5,-1 };
        //objects.push_back(player);
    }
    void WorldControler::updateDynamicObject()
    {
        for(LogicObject* object : WorldControler::dynamicObjects)
        {
            
        }
    }
    void WorldControler::startRender() {
        //TODO update camera
        static clock_t time = clock();
        clock_t now = clock();
        time = now;

        player->renderObject->demoBlock.shader->use();
        for (LogicObject* object : staticObjects) {
            object->renderObject->demoBlock.draw();
        }
        for (LogicObject* object : dynamicObjects) {
            object->renderObject->demoBlock.draw();
        }
        player->renderObject->demoBlock.draw();
    }
}