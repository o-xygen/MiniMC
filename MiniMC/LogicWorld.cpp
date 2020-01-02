#include "LogicWorld.h"
#include "CubicRoom.h"
#include "MeshMap.h"
namespace GameLogic {
    double WorldControler::camera[3];
    LogicObject* WorldControler::player;
    Vector3 WorldControler::cameraOffset;
    vector<LogicObject*>WorldControler::dynamicObjects;
    void* WorldControler::meshMap;
    //vector<LogicObject*>WorldControler::staticObjects;
    void WorldControler::initialize() {
        MeshMap* _meshMap = static_cast<MeshMap*>(meshMap);
        Physics::CubicRoom::initialize(_meshMap->size, 20, _meshMap->size);
        Physics::CubicRoom::offset = { 0, -5, 0 };

        for (int x = 0; x < _meshMap->size; ++x)
        {
            for (int z = 0; z < _meshMap->size; ++z)
            {
                for(int y : _meshMap->map[x][z].heights)
                {
                    LogicObject* logicObject = new LogicObject(true);
                    logicObject->setPosition(x, y, z);
                    logicObject->physicsObject->isRigid = true;
                    //staticObjects.push_back(logicObject);
                }
            }
        }

        player = new LogicObject(false);
        player->setPosition(0.0, 1.0, 0.0);
        player->physicsObject->isRigid = true;

        cameraOffset = { 0,0.5,-1 };
        //objects.push_back(player);
    }
    void WorldControler::updateDynamicObject()
    {
        for(LogicObject* object : dynamicObjects)
        {
            
        }
    }
    void WorldControler::startRender() {
        //TODO update camera

        /*
        for (LogicObject* object : staticObjects) {
            object->renderObject->demoBlock.draw();
        }
        */
        for (LogicObject* object : dynamicObjects) {
            //object->renderObject->demoBlock.draw();
        }

    }
}