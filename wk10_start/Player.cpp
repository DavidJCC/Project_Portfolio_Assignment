#include "Player.h"

Player::Player(float x, float y, float z, char* modelFile, char* modelTex) : Entity(x, y, z, modelFile, modelTex)
{
	m_health = 500;
	m_score = 0;
	m_noOfCoilsCollected = collectedCoils.size();
}

Player::~Player(void)
{
}

void Player::addCoilToInventory(EnergyCoil* coil)
{
	collectedCoils.push_back(coil);
}


