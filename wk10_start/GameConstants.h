#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <math.h>

#define _USE_MATH_DEFINES

const float P = atan(1.0f)*4.0f;
const float DEGTORAD = P / 180.0f;

/*******************************
		SCREEN DIMENSIONS
*******************************/
const int SCRN_W = 1280;
const int SCRN_H = 720;

/*******************************
		MAP ATTRIBUTES
*******************************/
const int MAP_X = 64;
const int MAP_Z = 64;
const float MAP_Y = 255.0f;
const float MAP_SCALE = 100.0f;

/*******************************
		    CAMERA
*******************************/
const float CAM_MAX = 200.0f;
const float CAM_MIN = 100.0f;

/*******************************
		    ZOMBIES
*******************************/
const int NUM_ZOMBIES = 6;
const int NUM_BONUS = 6;

/*******************************
		  EERGY COILS
*******************************/
const int NUM_COILS = 5;

/*******************************
		    PLAYER
*******************************/
const float WALK_SPD = 200.0f;
const float SPRINT_MULT = 1.5f;
const float PLR_START_X = (MAP_X * MAP_SCALE * 0.9f)/2;
const float PLR_START_Z = (MAP_X * MAP_SCALE * 0.9f)/-2;
const float PLAYER_SIZE = 5.0f;

/*******************************
		PLAYER ANIMATIONS
*******************************/
//animation speed
const float ANIM_SPD = 0.1f;

//idle
const int IDLE_START = 0;
const int IDLE_END = 39;

//run
const int RUN_START = 40;
const int RUN_END = 46;

//jump
const int JUMP_START = 66;
const int JUMP_END = 73;

//death
const int DEATH_START = 178;
const int DEATH_END = 183;

const float VIEW_ANGLE = 60.0f;
const float NEAR_CLIPPING = 0.1f;
const float FAR_CLIPPING = 7000.0f;

#endif