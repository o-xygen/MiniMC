#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "obj.h"

float rotate_y = 0;
float rotate_x = 0;//wasd控制视角转动

int flagPoints = 0;//键盘‘c’ 控制是否显示控制点
GLUnurbsObj* theNurb;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	//摄像机
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
	//wasd控制视角
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
	//pan
	glPushMatrix();
	glTranslatef(-3.0, -3.0, 0.7);
	glRotatef(180, 0, 1, 0);
	draw_pan();
	glPopMatrix();

	glPopMatrix();
	glFlush();
}

void nurbsError(GLenum errorCode) {
	const GLubyte* estring;
	estring = gluErrorString(errorCode);
	fprintf(stderr, "Nurbs Error: %s\n", estring);
	exit(0);
}

void init(void) {
	GLfloat Ambiente[4] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat Difusa[4] = { 0.7, 0.6, 0.6, 1.0 };
	GLfloat Especular[4] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat Position[4] = { 10.0, 10.0, 0, 1.0 };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambiente);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Especular);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
	gluNurbsCallback(theNurb, GLU_ERROR, (GLvoid(*)()) nurbsError);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'c':
	case 'C':
		flagPoints = !flagPoints;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
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
	default:
		break;
	}
}

void idle(void) {
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
