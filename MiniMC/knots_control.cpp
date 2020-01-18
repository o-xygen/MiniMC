#include "obj.h"
int flagPoints = 0;
GLUnurbsObj* theNurb;
//取一个16点的曲面并绘制的函数
void drawSurface(GLfloat surfaceVec[4][4][3]) {
    GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &surfaceVec[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
    gluEndSurface(theNurb);
    showPoints(surfaceVec);
}
//如果全局变量pointsFlag处于活动状态则显示点的函数
void showPoints(GLfloat surfaceVec[4][4][3]) {
    if (flagPoints) {
        glPointSize(5.0);
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                glVertex3f(surfaceVec[i][j][0], surfaceVec[i][j][1], surfaceVec[i][j][2]);
            }
        }
    	glEnd();
    	glEnable(GL_LIGHTING);
    }
}

void nurbsError(GLenum errorCode) {
    const GLubyte* estring;
    estring = gluErrorString(errorCode);
    fprintf(stderr, "Nurbs Error: %s\n", estring);
    exit(0);
}
void init() {
    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
}
void drawSurface2(GLfloat surfaceVec[4][9][3], int x, int y, int z) {
		int u, v;
		GLint un = 30;
		GLint vn = 30;

	    glMap2f(GL_MAP2_VERTEX_3, 0, 1, y*z, x, 0, 1, z, y, &surfaceVec[0][0][0]);
	    glEnable(GL_MAP2_VERTEX_3);
	    glEnable(GL_AUTO_NORMAL);
	    glBegin(GL_QUADS);
	    for (u = 0; u < un; u++) {
	        for (v = 0; v < vn; v++) {
	            glEvalCoord2f((GLfloat)v / vn, (GLfloat)(u+1) / un);
	            glEvalCoord2f((GLfloat)(v+1) / vn, (GLfloat)(u+1) / un);
	            glEvalCoord2f((GLfloat)(v+1) / vn, (GLfloat)u / un);
	            glEvalCoord2f((GLfloat)v / vn, (GLfloat)u / un);
	        }
	    }
	    glEnd();
}