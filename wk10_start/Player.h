#ifndef __ENTITY_H
#define __ENTITY_H

#include "entity.h"
#include "EnergyCoil.h"
#include <vector>

class Player :	public Entity
{
private:
	int m_score;
	int m_noOfCoilsCollected;
public:
	Player(float x, float y, float z, char* modelFile, char* modelTex); //sets the player's start position and loads a model and texture
	~Player(void);

	//set, get and update the score
	int getScore() { return m_score; }
	void setScore(int score) { m_score = score; }
	void updateScore(int score) { m_score += score; }

	int getCollectedCoils() { return m_noOfCoilsCollected; }
	void setCollectedCoils(int collectedCoils) { m_noOfCoilsCollected = collectedCoils; }
	void updateCollectedCoils(int collectedCoils) { m_noOfCoilsCollected += collectedCoils; }

	void resetPlayerStats();
};

#endif
