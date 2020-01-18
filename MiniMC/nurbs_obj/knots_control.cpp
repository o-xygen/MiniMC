#include "obj.h"

//取一个16点的曲面并绘制的函数
void drawSurface(GLfloat surfaceVec[4][4][3]) {
    GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &surfaceVec[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
    gluEndSurface(theNurb);
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