#include "pause.h"

GLfloat vertices[] = {
	-0.3f, 0.3f, 0.0f,
	0.3f, 0.3f, 0.0f,
	-0.3f,  -0.3f, 0.0f,
	0.3f,  -0.3f, 0.0f
};
GLuint indices[] = {
		0,1,2,
		1,2,3
};
GLuint VAO, VBO, EBO;

void pause::draw()
{
	shader->use();
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

pause::pause()
{
	shader = new Shader("shaders/pause.vert", "shaders/pause.frag");
}
