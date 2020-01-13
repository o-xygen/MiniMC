#include "Menu.h"
#include <iostream>
#include "glut.h"
void Menu::draw()
{
	shader->use();
	glm::mat4 ortho(1.f), view(1.f), model(1.f);
	view = glm::lookAt(glm::vec3{ 0.0, 0.0, 100 }, { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 });
	ortho = glm::ortho(-50, 50, -50, 50, -500, 500);
	ortho = glm::perspective(glm::radians(45.f), 1.f, 0.1f, 100.f);
	glOrtho(-50, 50, -50, 50, -500, 500);
	glm::vec3 pos = glm::vec3(20, 20, 50);
	model = glm::translate(model, pos);
	glTranslatef(25, 80, 50);
	shader->setInt("a", 0.5);
	shader->setInt("s", 0.8);
	shader->setMat4("ortho", ortho);
	shader->setMat4("view", view);
	shader->setMat4("model", model);
	if (press[0])
		glutSolidCube(8);
	else
		glutSolidCube(10);
	pos = glm::vec3(-40, 0, 0);
	model = glm::translate(model, pos);
	shader->setMat4("model", model);
	if (press[1])
		glutSolidCube(8);
	else
		glutSolidCube(10);
}

int Menu::changepress(float x, float y)
{
	y = 480 - y;
	if (y < 240 + 72 && y > 240 - 72 && x < 360 + 108 && x > 360 - 108 && paused)
	{
		paused = !paused;
		return 0;
	}
	if (y < 480 && y > 410 && !paused)
		if (x > 600 && x < 720)
		{
			press[0] = true;
			paused = !paused;
			return 0;
		}
		else if (x > 0 && x < 120)
		{
			press[1] = true;
			return 1;
		}
	//...
		else if (x > 55.5 && x < 60.5)
		{
			press[2] = true;
			return 2;
		}
		else if (x > 49.5 && x < 54.5)
		{
			press[3] = true;
			return 3;
		}
		else if (x > 43.5 && x < 49.5)
		{
			press[4] = true;
			return 4;
		}
	return -1;

}

void Menu::recoverpress()
{
	for (int i = 0; i < 5; i++)
		press[i] = false;
}