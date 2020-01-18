#include "Menu.h"
#include <iostream>
#include "glut.h"

GLfloat verticesm[] = {
	//rectangle
	-1.0f, 0.8f, 0.0f,
	-0.8f, 0.8f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	-0.8f, 1.0f, 0.0f,
	1.0f, 0.8f, 0.0f,
	0.8f, 0.8f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.8f, 1.0f, 0.0f,

	//cancle
	-0.935, 0.78, 0,
	-0.96, 0.75, 0,
	-0.835, 0.65, 0,
	-0.86, 0.625, 0,
	-0.86, 0.78, 0,
	-0.835, 0.75, 0,
	-0.96, 0.65, 0,
	-0.935, 0.625, 0,

	//pause
	0.86, 0.77, 0,
	0.89, 0.77, 0,
	0.86, 0.65, 0,
	0.89, 0.65, 0,
	0.86 + 0.05, 0.77, 0,
	0.89 + 0.05, 0.77, 0,
	0.86 + 0.05, 0.65, 0,
	0.89 + 0.05, 0.65, 0,
	
	-0.05, 0.02, 0,
	0.05, 0.02, 0,
	-0.05, -0.02, 0,
	0.05, -0.02, 0,
	
	0.02, 0.05, 0,
	-0.02, 0.05, 0,
	0.02, -0.05, 0,
	- 0.02, -0.05, 0
};

GLuint indicesm[] = {
		0,1,2,
		1,2,3,

		4,5,6,
		5,6,7,

		8,9,10,
		9,10,11,

		12,13,14,
		13,14,15,

		16,17,18,
		17,18,19,

		20,21,22,
		21,22,23,

		24, 25, 26,
		25,26,27,

		28,29,30,
		29,30,31,
		32,33,34,
		33,34,35
};

GLuint VAO2, VBO2, EBO2;

void Menu::draw()
{
	shader->use();
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesm), verticesm, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesm), indicesm, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO2);
	glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}

int Menu::changepress(float x, float y)
{
	y = 480 - y;
	if (y < 240 + 72 && y > 240 - 72 && x < 360 + 108 && x > 360 - 108 && paused)
	{
		paused = !paused;
		return 0;
	}
	if (y < 480 && y > 432 && !paused)
		if (x > 648 && x < 720)
		{
			press[0] = true;
			paused = !paused;
			return 0;
		}
		else if (x > 0 && x < 72)
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
