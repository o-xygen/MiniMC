#include "obj.h"

GLfloat table_up[4][4][3] = {
    {
        { -1.0, 1.0, 0.15},    { -0.5, 1.5, 0.15},
        { 0.5, 1.5, 0.15},     { 1.0, 1.0, 0.15}
    },
    {
        { -1.5, 0.5, 0.15},    { -0.5, 0.5, 0.15},
        { 0.5, 0.5, 0.15},    {1.5, 0.5, 0.15}
    },
    {
        { -1.5, -0.5, 0.15},     { -0.5, -0.5, 0.15},
        { 0.5, -0.5, 0.15},       { 1.5, -0.5, 0.15}
    },
    {
        { -1.0, -1.0, 0.15},    { -0.5, -1.5, 0.15},
        {0.5, -1.5, 0.15},       {1.0, -1.0, 0.15}
    }
};

GLfloat table_down[4][4][3] = {
    {
        { -1.0, 1.0, -0.15},    { -0.5, 1.5, -0.15},
        { 0.5, 1.5, -0.15},     { 1.0, 1.0, -0.15}
    },
    {
        { -1.5, 0.5, -0.15},    { -0.5, 0.5, -0.15},
        { 0.5, 0.5, -0.15},    {1.5, 0.5, -0.15}
    },
    {
        { -1.5, -0.5, -0.15},     { -0.5, -0.5, -0.15},
        { 0.5, -0.5, -0.15},       { 1.5, -0.5, -0.15}
    },
    {
        { -1.0, -1.0, -0.15},    { -0.5, -1.5, -0.15},
        {0.5, -1.5, -0.15},       {1.0, -1.0, -0.15}
    }
};



GLfloat
table_diffuse[] = { 0.7, 0.7, 0.7, 1.0 },
table_specular[] = { .2, .2, .2, 1.0 },
table_shininess[] = { 20.0 };



void draw_table(void) {//其实就是两块板夹起来
	glColor4f(0.8, 0.8, 0.8, .4);
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, table_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, table_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, table_shininess);


    glPushMatrix();
	    glPushMatrix();
	    	glScalef(5, 5, 1);
	    	drawSurface(table_up);
			glColor4f(0.8, 0.8, 0.8, .4);
			glRotatef(180, 0, 1, 0);
	    	drawSurface(table_down);
	    glPopMatrix();
		glPushMatrix();
			glScalef(5, 5, 1);
			drawSurface(table_down);
			glColor4f(0.8, 0.8, 0.8, .4);
			glRotatef(180, 0, 1, 0);
			drawSurface(table_up);
		glPopMatrix();

    glPopMatrix();
}
