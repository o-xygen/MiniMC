#pragma once
#include "Shader.h"
namespace GameLogic {
    class Camera {
    public:
        static void setProjection(float fovy, float aspect, float zNear, float zFar);
        static void setView(const glm::vec3&eyeTo,const glm::vec3&headCenter,const glm::vec3& up);

        static glm::mat4 projection;
        static glm::mat4 view;
    };
}