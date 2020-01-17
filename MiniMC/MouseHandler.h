#pragma once
namespace GameLogic
{
    class MouseHandler
    {
    private:
        static int lastX, lastY;
        static bool enter,first;
    public:
        static int width, height;
        static void mouseRegister(int x,int y);
        static void mouseClick(int button, int state, int x, int y);
        static void mouseEnter(int state);
        static void(*addNurbs)(int, int, int, int);
    };
}