#include "KeyboardHandler.h"
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/detail/func_trigonometric.inl>
#include <glm/mat4x4.hpp>
#include "LogicWorld.h"

namespace GameLogic
{
    void KeyboardHandler::keyboardRegister(unsigned char key, int x, int y)
    {
        switch (key)
        {
        case 'w':
        {
            giveVelocity(glm::vec4{ 0.f,0.f,1.f,1.f });
            break;
        }
        case 'a':
        {
            giveVelocity(glm::vec4{ 1.f,0.f,0.f,1.f });
            break;
        }
        case 's':
        {
            giveVelocity(glm::vec4{ 0.f,0.f,-1.f,1.f });
            break;
        }
        case 'd':
        {
            giveVelocity(glm::vec4{ -1.f,0.f,0.f,1.f });
            break;
        }
        case ' ':
        {
            tryJump();
            break;
        }
        default:
        {
            return;
        }
        }
    }
    const double jumpSpeed = 5.f;
    void KeyboardHandler::tryJump()
    {
        if(WorldControler::onTheGround)
        {
            WorldControler::player->physicsObject->velocity.y = jumpSpeed;
        }
    }
    const float moveSpeed = 0.05f;
    void KeyboardHandler::giveVelocity(const glm::vec4& direction)
    {
        Vector3& velocity = WorldControler::player->physicsObject->velocity;
        double rad = glm::radians(WorldControler::playerForward[0]);
        velocity.x = -sin(rad);
        velocity.z = cos(rad);

    }
}
