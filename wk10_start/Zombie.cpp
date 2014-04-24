#include "Zombie.h"


Zombie::Zombie(float x, float y, float z, char* modelFile, char* modelTex) : Entity(x, y, z, modelFile, modelTex)
{
	m_health = 50;
	m_lives = 1;
}


Zombie::~Zombie(void)
{
}