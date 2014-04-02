#pragma once
#include "MD2Model.h"
#include <string>

class Player :	public MD2Model{
	Vector position;
	int score;
	int lives;
	bool hasFlag;
	
public:
	bool isMoving;
	Player(char* modelFile, char* modelTexture, int x, int y, int z);
	~Player(void);

	int getScore() { return score; }
	void setScore(int score) { this->score = score; }
	int getLives() { return lives; }
	void setLives() { this->lives = lives; }

	void setMoving(bool moving) { this->isMoving = moving; }
	void move(int x, int y, int z);
	void animate();
	void render();
	std::string getFlagStatus();
};

