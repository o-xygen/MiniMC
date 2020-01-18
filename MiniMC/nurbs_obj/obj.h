#include <glut.h>
#include <stdlib.h>
#include <stdio.h>

extern GLUnurbsObj *theNurb;
extern GLUnurbsObj *theNurbEsp;


// 绘制功能
void drawSurface(GLfloat surfaceVec[4][4][3]);
void drawSurface2(GLfloat surfaceVec[4][9][3], int x, int y, int z);

//spoon
void draw_spoon(void);

//bowl
void draw_bowl(void);

//table
void draw_table(void);
