#include <glut.h>
#include <stdlib.h>
#include <stdio.h>

extern int flagPoints;
extern GLUnurbsObj *theNurb;
extern GLUnurbsObj *theNurbEsp;

//显示nurbs点的功能
void showPoints(GLfloat surfaceVec[4][4][3]);

// 绘制功能
void drawSurface(GLfloat surfaceVec[4][4][3]);
void drawSurface2(GLfloat surfaceVec[4][9][3], int x, int y, int z);
void init();
//spoon 0
void draw_spoon(double x, double y, double z);

//bowl 1
void draw_bowl(double x, double y, double z);

//table 2
void draw_table(double x, double y, double z);

//pan 3
void draw_pan (double x, double y, double z);