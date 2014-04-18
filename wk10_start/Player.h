#pragma once
#include "entity.h"
class Player :	public Entity
{
private:
	int m_score;
	bool m_hasFlag;
public:
	Player(float x, float y, float z, char* modelFile, char* modelTex); //sets the player's start position and loads a model and texture
	~Player(void);

	bool getFlagStatus() { return m_hasFlag; }

	int getScore() { return m_score; }
	void setScore(int score) { m_score = score; }
	void updateScore(int score) { m_score += score; } 

	void animate();
	void render();
};

