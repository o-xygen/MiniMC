#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
using std::string;

struct textureInfo
{
	int ID;
	int width, height;
};

unsigned int generateTexture(unsigned char* data, int width, int height, GLenum format);
textureInfo TextureFromFile(const string& filename);