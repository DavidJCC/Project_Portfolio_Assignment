#include "Player.h"


Player::Player(float x, float y, float z, char* modelFile, char* modelTex) : Entity(x, y, z, modelFile, modelTex)
{
	m_hasFlag = false;
	m_health = 500;
	m_score = 0;
}


Player::~Player(void)
{
}
