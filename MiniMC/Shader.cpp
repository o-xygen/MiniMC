#include "Shader.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

Shader::Shader(const string & vertexPath, const string & fragmentPath)
{
	// load code from file
	string vertexCode, fragmentCode;
	ifstream vertexFile(vertexPath), fragmentFile(fragmentPath);
	stringstream vertexStream, fragmentStream;
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();
	vertexFile.close();
	fragmentFile.close();
	vertexCode = vertexStream.str();
	fragmentCode = fragmentStream.str();

	// compile the code
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* c_vertexCode = vertexCode.c_str();
	glShaderSource(vertexShader, 1, &c_vertexCode, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* c_fragmentCode = fragmentCode.c_str();
	glShaderSource(fragmentShader, 1, &c_fragmentCode, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link the program
	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertexShader);
	glAttachShader(this->programID, fragmentShader);
	glLinkProgram(this->programID);

	glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(this->programID);
}

GLuint Shader::GetID()
{
	return this->programID;
}

void Shader::use()
{
	glUseProgram(this->programID);
}

void Shader::setInt(const string& name, int val)
{
	glUniform1i(glGetUniformLocation(this->programID, name.c_str()), val);
}

void Shader::setFloat(const string& name, int val)
{
	glUniform1f(glGetUniformLocation(this->programID, name.c_str()), val);
}

void Shader::setMat4(const string& name, const glm::mat4& val)
{
	glUniformMatrix4fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setVec3(const string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(this->programID, name.c_str()), x, y, z);
}

void Shader::setVec3(const string& name, const glm::vec3& val)
{
	glUniform3f(glGetUniformLocation(this->programID, name.c_str()), val.x, val.y, val.z);
}

void Shader::disable()
{
	glUseProgram(0);
}
