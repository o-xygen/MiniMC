#include "obj.h"

GLfloat head_spoon[4][4][3] = {
    {
        { -0.5, 0.80, 0},    { -0.15, 1.25, 0}, 
        { 0.15, 1.25, 0},     { 0.5, 0.80, 0}
    },
    {
        { -0.75, 0.5, 0},    { -0.5, 0.5, -0.5}, 
        { 0.5, 0.5, -0.5},    {0.75, 0.5, 0}
    }, 
    {
        { -1.0, -0.5, 0},     { -0.5, -0.5, -0.5}, 
        { 0.5, -0.5, -0.5},       { 1.0, -0.5, 0}
    }, 
    {
        { -0.5, -1.0, 0},    { -0.15, -1.25, 0}, 
        { 0.15, -1.25, 0},       { 0.5, -1.0, 0}
    }
};

GLfloat head_spoon_back[4][4][3] = {
    {
        { -0.5, 0.80, 0},    { -0.15, 1.25, 0}, 
        { 0.15, 1.25, 0},     { 0.5, 0.80, 0}
    },
    {
        { -0.75, 0.5, 0},    { -0.5, 0.5, 0.5}, 
        { 0.5, 0.5, 0.5},    {0.75, 0.5, 0}
    }, 
    {
        { -1.0, -0.5, 0},     { -0.5, -0.5, 0.5}, 
        { 0.5, -0.5, 0.5},       { 1.0, -0.5, 0}
    }, 
    {
        { -0.5, -1.0, 0},    { -0.15, -1.25, 0}, 
        { 0.15, -1.25, 0},       { 0.5, -1.0, 0}
    }
};

GLfloat handle_spoon[4][4][3] = {
    {
        { -0.10, 1.5, 0},    { -0.05, 1.5, 0}, 
        { 0.05, 1.5, 0},     { 0.10, 1.5, 0}
    }, 
    {
        { -0.10, 0.85, 0.35},    { -0.05, 0.85, 0.50}, 
        { 0.05, 0.85, 0.50},    {0.10, 0.85, 0.35}
    }, 
    {
        { -0.25, -0.5, 0},     { -0.15, -0.5, 0}, 
        { 0.15, -0.5, 0},       { 0.25, -0.5, 0}
    }, 
    {
        { -0.15, -1.25, 0},    { -0.15, -1.5, 0}, 
        {0.15, -1.5, 0},       {0.15, -1.25, 0}
    }
};

GLfloat handle_spoon_back[4][4][3] = {
    {
        { -0.10, 1.5, 0},    { -0.05, 1.5, 0}, 
        { 0.05, 1.5, 0},     { 0.10, 1.5, 0}
    }, 
    {
        { -0.10, 0.85, -0.35},    { -0.05, 0.85, -0.50}, 
        { 0.05, 0.85, -0.50},    {0.10, 0.85, -0.35}
    }, 
    {
        { -0.25, -0.5, 0},     { -0.15, -0.5, 0}, 
        { 0.15, -0.5, 0},       { 0.25, -0.5, 0}
    }, 
    {
        { -0.15, -1.25, 0},    { -0.15, -1.5, 0}, 
        {0.15, -1.5, 0},       {0.15, -1.25, 0}
    }
};

GLfloat
spoon_diffuse[] = { 0.7, 0.7, 0.7, 1.0 },
spoon_specular[] = { 1.0, 1.0, 1.0, 1.0 },
spoon_shininess[] = { 20.0 };


// 绘制小物件
void draw_spoon(void) {
    glColor4f(0.4, 0.4, 0.4, 0.4); // 银灰色
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, spoon_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spoon_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, spoon_shininess);

    glPushMatrix();
        glScalef(0.8, 0.8, 0.8);
        // handle
        glPushMatrix();
            glTranslatef(0, -2.67, 0); //1.5 + 1.25
            drawSurface(handle_spoon);
            glColor4f(0.4, 0.4, 0.4, 0.4);
        glPopMatrix();

		glPushMatrix();
			glTranslatef(0, -2.67, 0);
			glRotatef(180, 0, 1, 0);
			glTranslatef(0, 0, 0.01);
			drawSurface(handle_spoon_back);
			glColor4f(0.4, 0.4, 0.4, 0.4);
		glPopMatrix();

        // head
        glPushMatrix();
            drawSurface(head_spoon);
            glColor4f(0.4, 0.4, 0.4, 0.4);
        glPopMatrix();
		glPushMatrix();
			glRotatef(180, 0, 1, 0);
			glTranslatef(0, 0, 0.01);
			drawSurface(head_spoon_back);
		glPopMatrix();
        
    glPopMatrix();
}