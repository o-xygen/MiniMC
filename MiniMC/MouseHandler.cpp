#include <glut.h>
#include"MouseHandler.h"
#include "LogicWorld.h"

namespace GameLogic
{
    int MouseHandler::lastX, MouseHandler::lastY;
    int MouseHandler::width, MouseHandler::height;
    bool MouseHandler::enter = false,MouseHandler::first = false;
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
                double* playerRotate = WorldControler::playerFoward;

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
            /*
            if(enter == false)
            {
                enter = true;
                lastX = x;
                lastY = y;
            }
            else
            {
                // TODO about UI and other logic
                
            }*/
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
