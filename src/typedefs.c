#include "typedefs.h"




//Angles
float radians(float x){ return ((PI/180.0f)*x); }
float normalizeAngle(float x){
	if( x < 0){ return (x + 360.0f); }
	else if( x >= 360.0f) { return (x - 360.0f);}
	else { return x; }
}
///
float min(float a,float b){
	float x = (a < b) ? a : b;
	return x;
}
float max(float a,float b){
	float x = (a > b) ? a : b;
	return x;
}

//Vector2D
VECTOR2 vecAdd(const VECTOR2* A, const VECTOR2* B){ return (VECTOR2){A->x+B->x,A->y+B->y}; }
VECTOR2 vecSub(const VECTOR2* A, const VECTOR2* B){ return (VECTOR2){A->x-B->x,A->y-B->y}; }
float lenght(const VECTOR2* A) { return ( sqrt( (A->x*A->x) + (A->y*A->y) ) ); }
VECTOR2 normalizeVector(const VECTOR2* A){ float l = lenght(A); return (VECTOR2){A->x/l,A->y/l}; }
float crossProduct(const VECTOR2* A, const VECTOR2* B){ return ((A->x*B->y)-(A->y*B->x)); } 
// 0 - A and B are parallel, > 0 - B is to the left of a (counter clockwise turn), < 0 - B is to the right of A (clock wise turn
VECTOR2 rotatedVector(const VECTOR2*A,const float theta){
	VECTOR2 transform;
	transform.x = A->x * sinf(radians(theta)) - A->y * cosf(radians(theta));
	transform.y = (A->x * cosf(radians(theta)) + A->y * sinf(radians(theta)));
	return transform;
}

VECTOR2 Intersect(const VECTOR2*A,const VECTOR2* B, const VECTOR2* C, const VECTOR2* D){
	VECTOR2 p;
	float x = (A->x*B->y - A->y*B->x)*(C->x - D->x) - (A->x - B->x)*(C->x*D->y - C->y*D->x);
	float y = (A->x*B->y - A->y*B->x)*(C->y - D->y) - (A->y - B->y)*(C->x*D->y - C->y*D->x);
	float denominator = (A->x - B->x)*(C->y - D->y) - (A->y - B->y)*(C->x - D->x);
	if ( denominator == 0.0f) { return p; }
	//Save the point of intersection
	p.x = x/denominator; p.y = y/denominator;
	return p;
}


