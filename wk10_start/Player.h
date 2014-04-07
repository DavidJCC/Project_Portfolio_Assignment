#pragma once
#include "GameConstants.h"
#include "MD2Model.h"
#include <string>

class Player :	public MD2Model{
	std::string name;
	Vector position;
	Vector velocity;
	int health;
	int score;
	int lives;
	bool hasFlag;
	bool firstTime;
	bool isWalking;
	bool isJumping;
	bool isSprinting;
	
public:
	Player(char* name, char* modelFile,  char* modelTexture, int x, int y, int z);
	~Player(void);

	//setters and getters
	bool getFlagStatus() { return this->hasFlag; }
	int getScore() { return this->score; }
	void setScore(int score) { this->score = score; }
	int getLives() { return this->lives; }
	void setLives() { this->lives = lives; }
	void setName(std::string name) { this->name = name; }
	std::string getName() { return this->name; }
	void setHealth(int health) { this->health += health; }
	int getHealth() { return this->health; }
	void setPlayerMoving(bool setWalking){ isWalking = setWalking; }
	void setSprinting(bool setSprinting) { isSprinting = setSprinting; }
	void setJumping(bool setJumping) { isJumping = setJumping; }

	void setPos(float x, float y, float z);
	void setVel(float x, float y, float z);

	void move(float time);
	void update(float time);

	void animate();
	void render();
};

