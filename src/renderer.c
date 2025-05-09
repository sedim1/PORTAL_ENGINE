#include "renderer.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern Player player;

bool outsideScreen(VECTOR2I* s){
	//return ( (s->x < 0 || s->x > SW) && (s->y < 0 || s->y > SH)  );
	return ( s->x < 0 || s->x > SW || s->y < 0 || s->y > SH );
}

void pixel(int x,int y,RGB* color){
	//if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;
	const SDL_Rect rect = {x*PIXELSCALE,y*PIXELSCALE,PIXELSCALE,PIXELSCALE};
	SDL_SetRenderDrawColor(renderer,color->r,color->g,color->b,255);
	SDL_RenderFillRect(renderer,&rect);
}

void DDA(int X0, int Y0, int X1, int Y1,RGB* color) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) { 
	    pixel((int)X,(int)Y,color);
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
    } 
}

VECTOR2I ScreenCoord(VECTOR2* transform,float z){
	VECTOR2I screen = {0,0};
	float xScale = FOV/transform->y; float yScale = FOV/transform->y;
	screen.x = (int)(SW/2.0f - (transform->x * xScale) );
	screen.y = (int)(SH/2.0f - (z * yScale));
	return screen;
}


//Testing functions
void testFPS2DMap(){ // Render2D test relative to the first person view
	VECTOR2 center = {SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
	//Draw player at center of screen
	SDL_Rect p = {center.x-4,center.y-4,8,8};
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	SDL_RenderFillRect(renderer,&p);
	//Draw th eplayer direction
	SDL_RenderDrawLine(renderer,center.x,center.y,center.x,center.y - 13.0f);
	//Render a segment Example
	//render segment test relative to the player view
	VECTOR2 p1 = {155.0f,45.0f};
	VECTOR2 p2 = {155.0f,-45.0f};
	p1 = vecSub(&p1,&player.position);
	p2 = vecSub(&p2,&player.position);
	//Rotate points around players view
	VECTOR2 t1 = rotatedVector(&p1,player.yaw + 180.0f);
	VECTOR2 t2 = rotatedVector(&p2,player.yaw + 180.0f);
	//Draw those points on the map
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	//Points are leative to the players view
	SDL_RenderDrawLine(renderer,(int)(center.x + t1.x),(int)(center.y + t1.y),(int)(center.x+t2.x),(int)(center.y+t2.y));
	
}

//Draw a wall with a flat color
void drawFillWall(VECTOR2I* bottom1, VECTOR2I* bottom2, VECTOR2I* top1, VECTOR2I* top2,RGB* color){
	//Wall is drawn from left to right, so the variables are adjusted
	int xStart = bottom1->x; if ( xStart < 0 ){ xStart = 0; } if ( xStart > SW ){ xStart = SW; } 
	int xEnd = bottom2->x;   if ( xEnd > SW ){ xEnd = SW; } if ( xEnd < 0 ){ xEnd = 0; }
	int xSteps = xEnd - xStart;
	VECTOR2I dBottom, dTop;
	VECTOR2 bottom, top;
	/////////////////////////
	dBottom.x = bottom2->x - bottom1->x; dBottom.y = bottom2->y - bottom1->y;
	dTop.x = top2->x - top1->x; dTop.y = top2->y - top1->y;
	bottom.x = bottom1->x; bottom.y = bottom1->y;
	top.x = top1->x; top.y = top1->y;
	//////////////////////////////////////////////
	int bottomSteps = abs(dBottom.x) > abs(dBottom.y) ? abs(dBottom.x) : abs(dBottom.y);
	int topSteps = abs(dTop.x) > abs(dTop.y) ? abs(dTop.x) : abs(dTop.y);
	int steps = bottomSteps > topSteps ? bottomSteps : topSteps;
	//Calculate increment
	VECTOR2 bottomInc = { dBottom.x/(float)steps, dBottom.y/(float)steps};
	VECTOR2 topInc = { dTop.x/(float)steps, dTop.y/(float)steps};
	int lastX = -99999;
	for(int i = 0; i <= steps; i+=1){
		int x = (int)bottom.x;
		int yStart = top.y; if(yStart < 0) { yStart = 0; }
		int yEnd = bottom.y; if(yEnd > SH ) { yEnd = SH; }
		if( x != lastX && x >= 0 && x < SW ){
			for( int y = yStart; y <= yEnd; y+=1){
				pixel(x,y,color);
			}
		}
		bottom = vecAdd(&bottom,&bottomInc);
		top = vecAdd(&top,&topInc);
		lastX = x;
	}
}


void test3DRender(){
	//render segment test relative to the player view
	VECTOR2 p1 = {155.0f,45.0f};
	VECTOR2 p2 = {155.0f,-45.0f};
	p1 = vecSub(&p1,&player.position);
	p2 = vecSub(&p2,&player.position);
	//Rotate points around players view
	VECTOR2 t1 = rotatedVector(&p1,player.yaw);
	VECTOR2 t2 = rotatedVector(&p2,player.yaw);

	if (t1.y > 0 || t2.y > 0) {  //Draw Wall if is shown fully or partially in players view
		//Clip points if needed
		VECTOR2 i1  = Intersect(&t1,&t2,&( (VECTOR2){-zNear,zNear} ), &( (VECTOR2){-FOV/2,zFar} )); 
		VECTOR2 i2  = Intersect(&t1,&t2,&( (VECTOR2){zNear,zNear} ), &( (VECTOR2){FOV/2,zFar} ));
		//CLip the line if it crosses the player viewplane
		if(t1.y <= 0) { if(i1.y > 0 ) { t1.x = i1.x; t1.y = i1.y;} else {t1.x = i2.x; t1.y = i2.y;} }
		if(t2.y <= 0) { if(i1.y > 0 ) { t2.x = i1.x; t2.y = i1.y;} else {t2.x = i2.x; t2.y = i2.y;} }
		//Convert into screen cordinates - wall 1
		VECTOR2I top1 = ScreenCoord(&t2, 40.0f - player.z); //
		VECTOR2I top2 = ScreenCoord(&t1, 40.0f - player.z); //
		VECTOR2I bottom1 = ScreenCoord(&t2,-40.0f - player.z); 
		VECTOR2I bottom2 = ScreenCoord(&t1,-40.0f - player.z);
		VECTOR2I aux;
		//Arrange them respectively from left to right both bottom and top points
		if ( top1.x > top2.x) { 
			aux = top1; top1 = top2; top2=aux;
			aux = bottom1; bottom1 = bottom2; bottom2=aux;
		}
		RGB color = {255,0,0};
		RGB color2 = {255,255,255};
		/*printf("top1 %d %d\n",top1.x,top1.y);
		printf("top2 %d %d\n",top2.x,top2.y);
		printf("bottom1 %d %d\n",bottom1.x,bottom1.y);
		printf("bottom2 %d %d\n",bottom2.x,bottom2.y);*/
		drawFillWall(&bottom1, &bottom2, &top1, &top2,&color);
		DDA(top1.x,top1.y,top2.x,top2.y,&color2);
		DDA(bottom1.x,bottom1.y,bottom2.x,bottom2.y,&color2);
		DDA(top1.x,top1.y,bottom1.x,bottom1.y,&color2);
		DDA(top2.x,top2.y,bottom2.x,bottom2.y,&color2);
	}
}
