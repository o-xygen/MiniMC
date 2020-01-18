#pragma comment (lib,"glew32.lib")
#include <cstdlib>
#define _GLEW_STATIC
#include "GL/glew.h"
#include <glut.h>
#include "textfile.h"
#include <iostream>
#include "obj.h"


float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bAnim = false;
bool bWire = false;

bool teapotRotate = false;
GLint normalLength;
float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };
GLint cameraPosition;
float normalOffset = 0.05;

int wHeight = 0;
int wWidth = 0;
GLuint p1;

float rotate_y = 0;
float rotate_x = -45;//wasd控制视角转动
GLUnurbsObj* theNurb;

void _Draw_Scene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glUseProgram(p1);

	glPushMatrix();
	//摄像机
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 0.0, 1.0);
	//table
	draw_table();
	//spoon
	glPushMatrix();
	glTranslatef(2., -1., 0.5);
	draw_spoon();
	glPopMatrix();
	//bowl
	glPushMatrix();
	glTranslatef(0, 0, 0.8);
	draw_bowl();
	glPopMatrix();

	glPopMatrix();
}

void _updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	gluPerspective(40.0f, 1.0f, 1.0f, 800.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void _reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	_updateView(wHeight, wWidth);
}

void _idle()
{
	glutPostRedisplay();
}

float delta = 0.1f;
void _key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 'q': {exit(0); break; }

	case ' ': {bAnim = !bAnim; break; }

	case 'd':
		rotate_y += 5;
		break;
	case 'a':
		rotate_y -= 5;
		break;
	case 'w':
		rotate_x += 5;
		break;
	case 's':
		rotate_x -= 5;
		break;
	case 'z': {//todo
		eye[2] -= delta;
		center[2] -= delta;
		break;
	}
	case 'c': {//todo
		eye[2] += delta;
		center[2] += delta;
		break;
	}

	}
}


void _redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);

	glEnable(GL_DEPTH_TEST);

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glMatrixMode(GL_MODELVIEW);
	_Draw_Scene();						// Draw Scene

	if (bAnim) fRotate += 0.5f;

	//todo; hint: when you want to rotate the teapot, you may like to add another line here =)
	glutSwapBuffers();
}

void _shaderInit()
{
	GLuint v, f;
	char* vs = NULL, * fs = NULL;
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	vs = textFileRead("ivory.vert");
	fs = textFileRead("ivory.frag");
	const char* vv = vs;
	const char* ff = fs;
	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);
	free(vs);
	free(fs);
	glCompileShader(v);
	glCompileShader(f);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(v, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(v, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return;
	}
	glGetShaderiv(f, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(f, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return;
	}

	p1 = glCreateProgram();
	glAttachShader(p1, v);
	glAttachShader(p1, f);
	glLinkProgram(p1);

	glGetProgramiv(p1, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(p1, 512, NULL, infoLog);
	}



}

void _nurbsInit() {
	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(_redraw);
	glutReshapeFunc(_reshape);
	glutKeyboardFunc(_key);
	glutIdleFunc(_idle);

	glEnable(GL_CULL_FACE);
	glewInit();
	_nurbsInit();
	_shaderInit();

	glutMainLoop();
	return 0;
}


