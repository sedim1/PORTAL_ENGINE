#ifndef PLAYER_H
#define PLAYER_H

#include "typedefs.h"

void updatePlayerDirection();
void playerInit(VECTOR2* pos,float z, float pitch,  float yaw);
void movePlayer();

#endif
