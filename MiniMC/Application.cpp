#include "Application.h"
#include <glad/glad.h>
#include <glut.h>
#include "demoBlock.h"
#include <iostream>
#include "LogicWorld.h"
#include <fstream>
#include "json.hpp"
#include "block.h"
#include <chrono>
#include <ctime>
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "PhysicsFunction.h"
using json = nlohmann::json;
Application* glutWrapper::app = nullptr;
Shader* Application::blockShader = nullptr;
bool pp = true;

Application::Application(int width, int height) : windowWidth(width), windowHeight(height) {
	glutWrapper::app = this;
	meshMap = new MeshMap();
}

void Application::setup(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
    GameLogic::MouseHandler::width = windowWidth;
    GameLogic::MouseHandler::height = windowHeight;
	int windowHandle = glutCreateWindow("MiniMC");
	glutDisplayFunc(glutWrapper::redraw);
	glutReshapeFunc(glutWrapper::reshape);
    glutKeyboardFunc(GameLogic::KeyboardHandler::keyboardRegister);
    //glutMouseFunc(GameLogic::MouseHandler::mouseClick);
    //glutMotionFunc(GameLogic::MouseHandler::mouseRegister);
    glutPassiveMotionFunc(GameLogic::MouseHandler::mouseRegister);
    glutEntryFunc(GameLogic::MouseHandler::mouseEnter);
    //glutKeyboardUpFunc();
	glutIdleFunc(glutWrapper::idle);

	if (!gladLoadGL()) {
		std::cout << "something went wrong!" << std::endl;
		exit(-1);
	}
	glEnable(GL_DEPTH_TEST);

    //GameLogic::WorldControler::initialize(this);

	initBlockMap();
	// setup shaders
	blockShader = new Shader("shaders/planeVert.glsl", "shaders/planeFrag.glsl");
    GameLogic::WorldControler::menu = new Menu();
    GameLogic::WorldControler::menu->setshader();
    GameLogic::WorldControler::menu->setpause();
}

void Application::run() {
	glutMainLoop();
}

void Application::_redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	auto start = std::chrono::system_clock::now();


    if (pp) {
        Physics::PhysicsFunction::physicsUpdate();
        GameLogic::WorldControler::startRender();

        glEnable(GL_DEPTH_TEST);
        meshMap->render();
        glDisable(GL_DEPTH_TEST);
        GameLogic::WorldControler::menu->draw();
    }
    else {
        GameLogic::WorldControler::menu->showpause();
    }

	auto after = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = after - start;
	cout << "render time:" << elapsed_seconds.count() * 1000 << "ms" << endl;
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

void Application::initBlockMap()
{
	std::ifstream in("resources/models/blocks/grass_block.json");
	json j;
	try {
		in >> j;
	}
	catch(json::parse_error e){
		cout << e.what() << endl;
	}
	Block* block = new Block(j);
	BlockMap.insert({ block->getID(), block });
}
