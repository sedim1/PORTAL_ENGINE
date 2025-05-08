#include "renderer.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern Player player;

void pixel(int x,int y,RGB* color){
	const SDL_Rect rect = {x*PIXELSCALE,y*PIXELSCALE,PIXELSCALE,PIXELSCALE};
	SDL_SetRenderDrawColor(renderer,color->r,color->g,color->b,255);
	SDL_RenderFillRect(renderer,&rect);
}

void testFPS2DMap(){ // Render2D test relative to the first person view
	VECTOR2 center = {SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
	//Draw player at center of screen
	SDL_Rect p = {center.x-4,center.y-4,8,8};
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	SDL_RenderFillRect(renderer,&p);
	//Draw th eplayer direction
	SDL_RenderDrawLine(renderer,center.x,center.y,center.x+13.0f,center.y);
	//Render a segment Example
	//render segment test relative to the player view
	VECTOR2 p1 = {45.0f,45.0f};
	VECTOR2 p2 = {45.0f,-45.0f};
	p1 = vecSub(&p1,&player.position);
	p2 = vecSub(&p2,&player.position);
	//Rotate points around players view
	VECTOR2 t1 = rotatedVector(&p1,player.yaw);
	VECTOR2 t2 = rotatedVector(&p2,player.yaw);
	//Draw those points on the map
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	//Points are leative to the players view
	SDL_RenderDrawLine(renderer,(int)(center.x + t1.x),(int)(center.y + t1.y),(int)(center.x+t2.x),(int)(center.y+t2.y));
	
}
