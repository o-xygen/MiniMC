#pragma once
#include <glm/vec4.hpp>

namespace GameLogic {
    //static class, future will be changed into an single instance.
    class KeyboardHandler
    {
        KeyboardHandler();
        static void tryJump();
        static void giveVelocity(const glm::vec4& direction);
    public:
        static void keyboardRegister(unsigned char key,int x,int y);

    };
}
