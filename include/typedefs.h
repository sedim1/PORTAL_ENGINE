#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include<SDL2/SDL.h>
#define SW 100
#define SH 100
#define PIXELSCALE 8
#define SCREEN_WIDTH (SW * PIXELSCALE)
#define SCREEN_HEIGHT (SH * PIXELSCALE)

#define PI 3.14159265358979323846f

#define FOV 60.0f
#define zNear 0.001f
#define zFar 5.0f

typedef struct{
	int w,a,s,d,q,e,left,right,up,down;
}Keyboard;

//
float radians(float x);
float normalizeAngle(float x);
//
float min(float a,float b);
float max(float a,float b);

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
VECTOR2 Intersect(const VECTOR2*A,const VECTOR2* B, const VECTOR2* C,const VECTOR2* D);

typedef struct{
	int x, y;
}VECTOR2I;

typedef struct{ int r, g, b;}RGB;

typedef struct{
	VECTOR2 position;
	VECTOR2 direction;
	float z;
	float pitch; // x angle;
	float yaw; //y angle
}Player;


typedef struct {
	VECTOR2 p1, p2;
	int neighborSector; //Saves the id of 
}WALL;

typedef struct{
	int id;
	int nWalls;
	WALL* walls;
	int zfloor, zceiling;
}SECTOR;



#endif
