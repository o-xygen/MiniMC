#pragma once
class glutWrapper;
class Application {
public:
	Application(int width, int height);
	void setup(int argc, char* argv[]);
	void run();
private:
	int windowWidth, windowHeight;
	void _redraw();
	void _reshape(int w, int h);
	void _idle();
	friend glutWrapper;
};

class glutWrapper {
public:
	static void redraw() {
		app->_redraw();
	}
	static void reshape(int w, int h) {
		app->_reshape(w, h);
	}
	static void idle() {
		app->_idle();
	}
private:
	static Application* app;
	friend Application;
};