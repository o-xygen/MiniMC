#pragma once
#include <glad/glad.h>
#include "Shader.h"
class DemoBlock {
public:
    double position[3] = {};
    double rotate[3] = {};
	Shader* shader;
    DemoBlock();

    void draw();

	~DemoBlock();
private:
	GLuint VAO, VBO;
	GLuint textureID;
};