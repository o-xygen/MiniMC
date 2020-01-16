#include "KeyboardHandler.h"
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/detail/func_trigonometric.inl>
#include <glm/mat4x4.hpp>
#include "LogicWorld.h"
#include "CubicRoom.h"

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
    void KeyboardHandler::tryJump()
    {
        if(WorldControler::onTheGround)
        {
            WorldControler::player->physicsObject->velocity.y = Physics::jumpSpeed;
            WorldControler::onTheGround = false;
        }
    }
    void KeyboardHandler::giveVelocity(const glm::vec4& direction)
    {
        Vector3& velocity = WorldControler::player->physicsObject->velocity;
        glm::vec3 res = glm::rotate(glm::mat4{ 1 }, glm::radians((float)WorldControler::playerForward[0]), glm::vec3{ 0.f,-1.f,0.f })
            * direction;
        velocity.x = res.x * Physics::moveSpeed;
        velocity.z = res.z * Physics::moveSpeed;
        Physics::isMoving = true;
    }
}
