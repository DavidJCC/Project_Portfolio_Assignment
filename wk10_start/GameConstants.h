#pragma once

//game
const int SCRN_W = 800;
const int SCRN_H = 600;

const int MAP_X = 64;
const int MAP_Z = 64;
const float MAP_Y = 255.0f;
const float MAP_SCALE = 50.0f;
const float PLAYER_SIZE = 5.0f;
const int NUM_OBJS = 6;

//camera
const float CAM_MAX = 200.0f;
const float CAM_MIN = 100.0f;

//player
const float WALK_SPD = 200.0f;
const float SPRINT_SPD = 300.0f;

//player animation
const int RUN_START = 40;
const int RUN_END = 46;
const int NOT_MOVING_START = 0;
const int NOT_MOVING_END = 40;
const float ANIM_SPEED = 0.1f;