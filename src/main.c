///SDL TEMPLATE PROGRAM
#include "engine.h"

bool Init();
void mainLoop();
void End();
void Display();
void HandleEvents();

//window to render
SDL_Window* window = NULL;
//The surface contained by the window
SDL_Renderer* renderer = NULL;
bool isRunning = true;
float deltaTime = 0.0f;
Keyboard key = {0,0,0,0,0,0,0,0,0,0};

int main(int argc, char* argv[]){
	if(!Init())
		return -1;
	mainLoop();
	End();
	return 0;
}

bool Init(){
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); return false;
	}

	//Create window
        window = SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); return false;
        }
	//Get window surface
        renderer = SDL_CreateRenderer(window,-1,0);
        if( renderer == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); return false;
        }
	return true;
}


void mainLoop(){
	float lastTime = 0.0f;
	playerInit( &( (VECTOR2){0.0f,0.0f} ) ,0.0f,0.0f,0.0f);
	while(isRunning){
		float currentTime = (float)(SDL_GetTicks()/1000.0f);
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		HandleEvents();
		//Game logic goes here
		movePlayer();
		//Start rendering after processing the game logic
		Display();
	}
}

void Display(){
	SDL_SetRenderDrawColor(renderer,0,0,0,255); //Clear screen color
	SDL_RenderClear(renderer); //Clear 
	//Rendering logic goes here
	testFPS2DMap();
	SDL_RenderPresent(renderer); //Render the final image final image
}

void End(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Exiting\n");
}

void HandleEvents(){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
					case SDLK_ESCAPE:
						isRunning = false;
						break;
					case SDLK_q:
						key.q = 1;
						break;
					case SDLK_e:
						key.e = 1;
						break;
					case SDLK_a:
						key.a = 1;
						break;
					case SDLK_d:
						key.d = 1;
						break;
					case SDLK_w:
						key.w = 1;
						break;
					case SDLK_s:
						key.s = 1;
						break;
					case SDLK_UP:
						key.up = 1;
						break;
					case SDLK_DOWN:
						key.down = 1;
						break;
					case SDLK_LEFT:
						key.left = 1;
						break;
					case SDLK_RIGHT:
						key.right = 1;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch(e.key.keysym.sym){
					case SDLK_q:
						key.q = 0;
						break;
					case SDLK_e:
						key.e = 0;
						break;
					case SDLK_a:
						key.a = 0;
						break;
					case SDLK_d:
						key.d = 0;
						break;
					case SDLK_w:
						key.w = 0;
						break;
					case SDLK_s:
						key.s = 0;
						break;
					case SDLK_UP:
						key.up = 0;
						break;
					case SDLK_DOWN:
						key.down = 0;
						break;
					case SDLK_LEFT:
						key.left = 0;
						break;
					case SDLK_RIGHT:
						key.right = 0;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}
