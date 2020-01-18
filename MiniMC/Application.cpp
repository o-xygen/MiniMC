#include "Application.h"
#include "textfile.h"
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
#include "obj.h"
#include "Object.h"
using json = nlohmann::json;
Application* glutWrapper::app = nullptr;
Shader* Application::blockShader = nullptr;
bool pp = true;
Application* Application::instance;

GLuint p1;
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
    glutMouseFunc(GameLogic::MouseHandler::mouseClick);
    //glutMotionFunc(GameLogic::MouseHandler::mouseRegister);
    glutPassiveMotionFunc(GameLogic::MouseHandler::mouseRegister);
    glutEntryFunc(GameLogic::MouseHandler::mouseEnter);
    instance = this;
    GameLogic::MouseHandler::addNurbs = addNurbs;
    //glutKeyboardUpFunc();
	glutIdleFunc(glutWrapper::idle);

	if (!gladLoadGL()) {
		std::cout << "something went wrong!" << std::endl;
		exit(-1);
	}
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

	initBlockMap();
    GameLogic::WorldControler::initialize();
	// setup shaders
	blockShader = new Shader("shaders/planeVert.glsl", "shaders/planeFrag.glsl");
    init();//nurbs init
    _shaderInit();
    GameLogic::WorldControler::menu = new Menu();
    GameLogic::WorldControler::menu->setshader();
    GameLogic::WorldControler::menu->setpause();
}

void Application::run() {
	glutMainLoop();
}
static vector<pair<glm::vec3, int>> nurbs{};
void Application::addNurbs(int x, int y, int z, int type) {
    ++y;
    for (int y0 : instance->meshMap->map[x][z].heights) {
        if (y0 == y)
            return;
    }

    GameLogic::LogicObject* logicObject = new GameLogic::LogicObject(true);
    logicObject->setPosition(x + 0.5, y + 0.5, z + 0.5);
    logicObject->physicsObject->isRigid = true;
    logicObject->physicsObject->bound[0] = { -0.5,-0.5,-0.5 };
    logicObject->physicsObject->bound[1] = { 0.5,0.5,0.5 };
    instance->meshMap->blockPosMap.begin()->second.push_back(vec3{ x, y, z });
    nurbs.push_back(pair <vec3, int> {vec3{ x,y,z }, type});
}
static void drawNurbs() {
    glUseProgram(p1);
    for (pair<glm::vec3, int> object : nurbs) {
        switch (object.second) {
        case 0: {
            draw_spoon(object.first.x + 0.5, object.first.y + 0.5, object.first.z + 0.5);
            break;
        }
        case 1: {

            break;
        }
        case 2: {

            break;
        }
        case 3: {

            break;
        }
        }
    }
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

        //glEnable(GL_DEPTH_TEST);
        //drawNurbs();

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
