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
    const float moveSpeed = 1.f;
    void KeyboardHandler::giveVelocity(const glm::vec4& direction)
    {
        glm::mat4 matrix{ 1.f };
        matrix = glm::rotate(matrix, glm::radians((float)WorldControler::playerFoward[0]), glm::vec3{ 0.f,-1.f,0.f });
        glm::vec3 velocity = matrix * direction * moveSpeed;
        Vector3& vector3 = WorldControler::player->physicsObject->velocity;
        vector3.x = velocity.x;
        vector3.z = velocity.z;

    }
}
