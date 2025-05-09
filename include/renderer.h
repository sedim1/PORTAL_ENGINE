#ifndef RENDERER_H
#define RENDERER_H

#include "typedefs.h"

bool outsideScreen(VECTOR2I* s);
VECTOR2I ScreenCoord(VECTOR2* transform, float z);
VECTOR2I clampScreenCoord(VECTOR2I* s);
void DDA(int X0, int Y0, int X1, int Y1,RGB* color) ;
void pixel(int x, int y,RGB* color);



//Testing functions
void drawFillWall(VECTOR2I* bottom1, VECTOR2I* bottom2, VECTOR2I* top1, VECTOR2I* top2,RGB* color);
void testFPS2DMap();
void test3DRender();

#endif
