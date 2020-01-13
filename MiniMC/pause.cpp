#include "pause.h"

GLfloat vertices[] = {
	-0.3f, 0.3f, 0.0f,
	0.3f, 0.3f, 0.0f,
	-0.3f,  -0.3f, 0.0f,
	0.3f,  -0.3f, 0.0f
};
GLfloat vertices2[] = {
	-0.15f, 0.2f, -0.5f,
	-0.15f, -0.2f, -0.5f,
	0.15f, 0.0f, -0.5f
};
GLuint indices[] = {
		0,1,2,
		1,2,3
};
GLuint indices2[] = {
		0,1,2,
};
GLuint VAO, VBO, EBO;
GLuint VAO2, VBO2, EBO2;

//void pause::texload()
//{
//	//int w = 0, h = 0;
//	/*glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);*/
//	//img = SOIL_load_image("pause.png", &w, &h, 0, SOIL_LOAD_RGB);
//	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
//	//glGenerateMipmap(GL_TEXTURE_2D);
//	//SOIL_free_image_data(img);
//	//glBindTexture(GL_TEXTURE_2D, 0);
//	auto info = TextureFromFile("resources/textures/pause.png");
//
//	LoadedTextures.insert({ info.ID, true });
//	glActiveTexture(GL_TEXTURE0);
//	texture = info.ID;
//	glBindTexture(GL_TEXTURE_2D, texture);
//}

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

	//
	shader2->use();
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

pause::pause()
{
	shader = new Shader("shaders/pause.vert", "shaders/pause.frag");
	shader2 = new Shader("shaders/pause.vert", "shaders/pause2.frag");
	//texload();
}