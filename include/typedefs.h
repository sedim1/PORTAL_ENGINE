#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include<SDL2/SDL.h>
#define SW 256
#define SH 180
#define PIXELSCALE 4
#define SCREEN_WIDTH (SW*PIXELSCALE)
#define SCREEN_HEIGHT (SH*PIXELSCALE)

#define PI 3.14159265358979323846f

#define FOV 60.0f

typedef struct{
	int w,a,s,d,q,e,left,right,up,down;
}Keyboard;

float radians(float x);
float normalizeAngle(float x);

typedef struct{ 
	float x, y; 
}VECTOR2;

VECTOR2 vecAdd(const VECTOR2* A, const VECTOR2* B);
VECTOR2 vecSub(const VECTOR2* A, const VECTOR2* B);
float lenght(const VECTOR2* A);
VECTOR2 normalizeVector(const VECTOR2* A);
float crossProduct(const VECTOR2* A, const VECTOR2* B);
// 0 - A and B are parallel, > 0 - B is to the left of a (counter clockwise turn), < 0 - B is to the right of A (clock wise turn
VECTOR2 rotatedVector(const VECTOR2*A,const float theta);


typedef struct{ int r, g, b;}RGB;

typedef struct{
	VECTOR2 position;
	VECTOR2 direction;
	float z;
	float pitch; // x angle;
	float yaw; //y angle
}Player;



#endif
