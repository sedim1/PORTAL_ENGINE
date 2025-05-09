#include "player.h"

extern float deltaTime;
extern Keyboard key;
Player player;
float pSpeed = 80.0f;
float pRot = 170.0f;

void updatePlayerDirection(){

	player.direction.x = cos(radians(player.yaw));
	player.direction.y = sin(radians(player.yaw));
}

void playerInit(VECTOR2* pos,float z, float pitch,  float yaw){
	player.position = *pos;
	player.z = z;
	player.pitch = pitch;
	player.yaw = yaw;
	updatePlayerDirection();
}

void movePlayer(){
	if(key.left == 1) { 
		player.yaw -= (pRot * deltaTime); player.yaw = normalizeAngle(player.yaw); 
		updatePlayerDirection();
	}
	if(key.right == 1) { 
		player.yaw += (pRot * deltaTime); player.yaw = normalizeAngle(player.yaw); 
		updatePlayerDirection();
	}
	if(key.q == 1){
		player.z += deltaTime * 80.0f;
	}
	if(key.e == 1){
		player.z -= deltaTime * 80.0f;
	}

	VECTOR2 velocity = {player.direction.x*pSpeed*deltaTime,player.direction.y*pSpeed*deltaTime};
	VECTOR2 strafe = {-player.direction.y*pSpeed*deltaTime,player.direction.x*pSpeed*deltaTime};
	if(key.w == 1){ 
		player.position = vecAdd(&player.position,&velocity);
	}
	if(key.s == 1){ 
		player.position = vecSub(&player.position,&velocity);
	}
	if(key.a == 1){ 
		player.position = vecSub(&player.position,&strafe);
	}
	if(key.d == 1){ 
		player.position = vecAdd(&player.position,&strafe);
	}
	
}
