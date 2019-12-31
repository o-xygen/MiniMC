#include "Application.h"
#include <glad/glad.h>
#include <glut.h>
#include "demoBlock.h"
#include <iostream>
#include "LogicWorld.h"

Application* glutWrapper::app = nullptr;

Application::Application(int width, int height) : windowWidth(width), windowHeight(height) {
	glutWrapper::app = this;
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

    GameLogic::WorldControler::initialize();
}

void Application::run() {
	glutMainLoop();
}

void Application::_redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GameLogic::WorldControler::startRender();
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
