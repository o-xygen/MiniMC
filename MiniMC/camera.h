#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// todo
class Camera
{
public:
	glm::mat4 getViewMat() {
		return glm::lookAt(glm::vec3{ 40.f, 2.f, 20.f }, { 50.f, 0.f, 50.f }, { 0.f, 1.f,0.f });
	}

	glm::mat4 getProjectionMat() {
		return glm::perspective(glm::radians(45.f), 1.f, 0.1f, 100.f);
	}
private:

};
extern Camera camera;