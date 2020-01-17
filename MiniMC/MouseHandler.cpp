#include <glut.h>
#include"MouseHandler.h"
#include "LogicWorld.h"
#include "PhysicsFunction.h"
#include "camera.h"

namespace GameLogic
{
    int MouseHandler::lastX, MouseHandler::lastY;
    int MouseHandler::width, MouseHandler::height;
    bool MouseHandler::enter = false,MouseHandler::first = false;
    void(*MouseHandler::addNurbs)(int, int, int, int) = nullptr;
    const static double xMotion = 1.0,yMotion = 1.0;
    void MouseHandler::mouseRegister(int x, int y)
    {
        if(enter)
        {
            if(first)
            {
                lastX = x;
                lastY = y;
                first = false;
            }
            else
            {
                double* playerRotate = WorldControler::playerForward;

                playerRotate[0] += (x - lastX) * xMotion;
                if (playerRotate[0] < 0)
                {
                    playerRotate[0] += 360;
                }
                else if (playerRotate[0] > 360)
                {
                    playerRotate[0] -= 360;
                }

                playerRotate[1] += (y - lastY) * yMotion;
                if (playerRotate[1] < -80)
                {
                    playerRotate[1] = -80;
                }
                if (playerRotate[1] > 80)
                {
                    playerRotate[1] = 80;
                }
                //printf("rotate[0](x):%lf\trotate[1](y):%lf\n", playerRotate[0], playerRotate[1]);
                lastX = x;
                lastY = y;
            }
        }
    }
    void MouseHandler::mouseClick(int button, int state, int x, int y)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            switch (state)
            {
            case GLUT_DOWN:
            {
                if (pp) {// add mesh objects
                    WorldControler::updateCamera();
                    PhysicsComponent* hit = nullptr;
                    Vector3* point = new Vector3{};
                    if (Physics::PhysicsFunction::doRaycast(
                        Vector3{ camera.headPosition.x, camera.headPosition.y, camera.headPosition.z },
                        Vector3{ camera.lookTo.x - camera.headPosition.x, camera.lookTo.y - camera.headPosition.y, camera.lookTo.z - camera.headPosition.z },
                        hit, point)) {
                        addNurbs(floor(hit->logicObject->position.x), floor(hit->logicObject->position.y), floor(hit->logicObject->position.z), 0);
                        //cout << point->x << " " << point->y << " " << point->z << "\n";
                        //cout << "(" << hit->logicObject->position.x << "," << hit->logicObject->position.y << "," << hit->logicObject->position.z << " " << ")\n";
                    }
                }
                int ret = GameLogic::WorldControler::menu->changepress(x, y);
                if (ret == 0)
                {
                    pp = !pp;
                    //function
                }
                else if (ret == 1)
                {
                    exit(0);
                    //function
                }
                break;
            }
            case GLUT_UP:
                GameLogic::WorldControler::menu->recoverpress();
            }
        }
    }
    void MouseHandler::mouseEnter(int state)
    {
        if(state == GLUT_ENTERED)
        {
            first = true;
            enter = true;
        }
        else
        {
            enter = false;
        }
    }
}
