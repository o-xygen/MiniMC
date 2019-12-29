#pragma once
#include <glad/glad.h>
#include "Shader.h"
class DemoBlock {
public:
    double position[3];
    DemoBlock();

    void draw();

	~DemoBlock();
private:
	GLuint VAO, VBO;
	Shader* shader;
	GLuint textureID;
};