#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// todo
class Camera
{
public:
    const glm::vec4 originHead{ 0,0,0,1 }, originLookTo{ 0,0,1,1 }, originUp{ 0,1,0,1 };
    glm::vec3 headPosition{ -2.f, 4.f, -2.f }, lookTo{ 4.f, 0.f, 4.f }, up{ 0.f, 1.f,0.f };
	glm::mat4 getViewMat() {
		return glm::lookAt(headPosition, lookTo, up);
	}

	glm::mat4 getProjectionMat() {
		return glm::perspective(glm::radians(80.f), 1.5f, 0.1f, 100.f);
	}
private:

};
extern Camera camera;