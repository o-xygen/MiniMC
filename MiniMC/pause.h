#pragma once
#if defined(WIN32)
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "glut.h"
#include "utils.h"
#include "LoadedTexture.h"

class pause
{
public:
	pause();
	void draw();
private:
	GLuint texture;
	unsigned char * img;
	Shader* shader;
};

