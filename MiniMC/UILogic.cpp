void Application::_mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		switch (state)
		{
		case GLUT_DOWN:
		{
			int ret = menu->changepress(x, y);
			if (ret == 0)
			{
				pp = !pp;
				//function
			}
			else if (ret == 1)
			{
				exit(0);
				//function
			}
			break;
		}
		case GLUT_UP:
			menu->recoverpress();
		}
	}
}

void Application::_redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Physics::PhysicsFunction::physicsUpdate();

	auto start = std::chrono::system_clock::now();
	if (pp) {
		GameLogic::WorldControler::startRender();
		glEnable(GL_DEPTH_TEST);
		meshMap->render();
		glDisable(GL_DEPTH_TEST);
		menu->draw();
	}
	else {
		menu->showpause();
	}

	glutSwapBuffers();
}