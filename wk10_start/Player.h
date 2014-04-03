#pragma once
#include "GameConstants.h"
#include "MD2Model.h"
#include <string>

class Player :	public MD2Model{
	Vector position, velocity;
	int score;
	int lives;
	bool hasFlag, firstTime, isMoving, bbSwitch;
	
public:
	Player(char* modelFile, char* modelTexture, int x, int y, int z);
	~Player(void);

	int getScore() { return score; }
	void setScore(int score) { this->score = score; }
	int getLives() { return lives; }
	void setLives() { this->lives = lives; }

	void setPlayerMoving(bool setMoving){ isMoving = setMoving; }

	void setPos(float x, float y, float z);
	void setVel(float x, float y, float z);

	void move(float time);
	void update(float time);

	void animate();
	void render();
	void switchBB(bool bbSwitch) { this->bbSwitch = bbSwitch; }
	std::string getFlagStatus();
};

