#include "typedefs.h"


//Angles
float radians(float x){ return ((PI/180.0f)*x); }
float normalizeAngle(float x){
	if( x < 0){ return (x + 360.0f); }
	else if( x >= 360.0f) { return (x - 360.0f);}
	else { return x; }
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
	transform.x = A->x * cos(radians(theta)) - A->y * sin(radians(theta));
	transform.y = -(A->x * sin(radians(theta)) + A->y * cos(radians(theta)));
	return transform;
}


