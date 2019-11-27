#include "Application.h"

int main(int argc, char* argv[]) {
	Application* app = new Application(480, 480);
	app->setup(argc, argv);
	app->run();
	delete app;
	return 0;
}