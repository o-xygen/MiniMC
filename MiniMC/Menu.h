#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "pause.h"

class Menu
{
public:
	Menu() {
		paused = true;
		for (int i = 0; i < 5; i++)
			press[i] = false;
	}
	int changepress(float x, float y);
	void recoverpress();
	void draw();
	void setshader() {
		shader = new Shader("shaders/menu.vert", "shaders/menu.frag");
	}
	void setpause() {
		p = new pause();
	}
	void showpause() {
		p->draw();
	}
private:
	float view[4];
	bool press[5];
	Shader* shader;
	bool paused;
	pause* p;
	
};

