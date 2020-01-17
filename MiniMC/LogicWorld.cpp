#include "LogicWorld.h"
#include "CubicRoom.h"
#include "MeshMap.h"
namespace GameLogic {
    LogicObject* WorldControler::player;
    bool WorldControler::onTheGround;
    double WorldControler::playerForward[2];
    Vector3 WorldControler::cameraOffset;
    vector<LogicObject*>WorldControler::dynamicObjects;
    void* WorldControler::meshMap;
    Menu* WorldControler::menu = nullptr;
    //vector<LogicObject*>WorldControler::staticObjects;
    void WorldControler::initialize() {
        MeshMap* _meshMap = static_cast<MeshMap*>(meshMap);
        Physics::CubicRoom::offset = { 0, -5, 0 };
        Physics::CubicRoom::initialize(_meshMap->size, 20, _meshMap->size);

        for (int x = 0; x < _meshMap->size; ++x)
        {
            for (int z = 0; z < _meshMap->size; ++z)
            {
                for(int y : _meshMap->map[x][z].heights)
                {
                    LogicObject* logicObject = new LogicObject(true);
                    logicObject->setPosition(x + 0.5, y + 0.5, z + 0.5);
                    logicObject->physicsObject->isRigid = true;
                    logicObject->physicsObject->bound[0] = { -0.5,-0.5,-0.5 };
                    logicObject->physicsObject->bound[1] = { 0.5,0.5,0.5 };
                    //staticObjects.push_back(logicObject);
                }
            }
        }

        int maxY = -0x7fffffff;//may be 64 bit?
        for (int y : _meshMap->map[0][0].heights)
        {
            if(y > maxY)
            {
                maxY = y;
            }
        }
        onTheGround = true;
        player = new LogicObject(false);
        player->setPosition(0.5, maxY + 1 + 0.5, 0.5);
        player->physicsObject->isRigid = true;
        player->physicsObject->bound[0] = { -0.2,-0.5,-0.2 };
        player->physicsObject->bound[1] = { 0.2,1.5,0.2 };

        cameraOffset = { 0,1,0 };
        //objects.push_back(player);
    }
    void WorldControler::startRender() {
        updateCamera();

        /*
        for (LogicObject* object : staticObjects) {
            object->renderObject->demoBlock.draw();
        }
        for (LogicObject* object : dynamicObjects) {
            object->renderObject->demoBlock.draw();
        }
        */

    }
    static const glm::vec4 xDirection{ 1.f,0.f,0.f,1.f };
    void WorldControler::updateCamera()
    {
        Vector3 temp = player->position + cameraOffset;
        glm::vec4 translate{ temp.x,temp.y,temp.z,0 };

        double* playerRotation = WorldControler::playerForward;
        glm::mat4 rotateWithY = glm::rotate(glm::mat4{ 1 }, glm::radians((float)playerRotation[0]), glm::vec3{ 0.f,-1.f,0.f });
        glm::vec3 newDirection = rotateWithY * xDirection;
        glm::mat4 cameraRotation = glm::rotate(glm::mat4{ 1 }, glm::radians((float)playerRotation[1]), newDirection);
        cameraRotation = cameraRotation * rotateWithY;

        camera.headPosition = /*cameraRotation* */camera.originHead + translate;
        camera.lookTo = cameraRotation * camera.originLookTo + translate;
        //camera.up = cameraRotation * camera.originUp + translate;
    }
}