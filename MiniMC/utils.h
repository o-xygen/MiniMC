#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
using std::string;

unsigned int generateTexture(unsigned char* data, int width, int height, GLenum format);
int TextureFromFile(const string& filename);