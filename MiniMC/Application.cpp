#include "Application.h"
#include <glad/glad.h>
#include <glut.h>
#include "demoBlock.h"
#include <iostream>

Application* glutWrapper::app = nullptr;

Application::Application(int width, int height) : windowWidth(width), windowHeight(height) {
	glutWrapper::app = this;
	meshMap = new MeshMap();
}

void Application::setup(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	int windowHandle = glutCreateWindow("MiniMC");
	glutDisplayFunc(glutWrapper::redraw);
	glutReshapeFunc(glutWrapper::reshape);
	glutIdleFunc(glutWrapper::idle);

	if (!gladLoadGL()) {
		std::cout << "something went wrong!" << std::endl;
		exit(-1);
	}
	glEnable(GL_DEPTH_TEST);
}

void Application::run() {
	glutMainLoop();
}

void Application::_redraw()
{
	static DemoBlock demoBlock;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	demoBlock.draw();
	glutSwapBuffers();
}

void Application::_reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Application::_idle()
{
	glutPostRedisplay();
}
