#ifndef PLAYER_H
#define PLAYER_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "GameConstants.h"
#include "MD2Model.h"

class Player :	public MD2Model
{
private:
	std::string m_name;
	char* m_modelFile;
	char* m_textureFile;
	Vector m_velocity;
	Vector m_direction;
	float m_playerSpeed;
	int m_health;
	int m_score;
	int m_lives;
	bool m_hasFlag;
	bool m_isMoving;
	bool m_firstTime;
	bool m_isWalking;
	bool m_isSprinting;
	bool m_isJumping;
	bool m_bbRender;
	
public:
	Player(char* name, int x, int y, int z);
	~Player(void);

	//setters and getters
	bool getFlagStatus() { return m_hasFlag; }

	int getScore() { return m_score; }
	void setScore(int score) { m_score = score; }

	int getLives() { return m_lives; }
	void setLives(int lives) { m_lives = lives; }

	void setName(std::string name) { m_name = name; }
	std::string getName() { return m_name; }

	void setHealth(int health) { m_health += health; }
	int getHealth() { return m_health; }

	void setWalking(bool setWalking);
	void setSprinting(bool setSprinting);
	void setJumping(bool setJumping);

	void setBBRender(bool bbRender) { m_bbRender = bbRender; } //render the bounding box
	bool getBBRender() { return m_bbRender; }

	void setPos(float x, float y, float z);
	void setVel(float x, float y, float z);
	void move(float time);
	void update(float time);
	void stopMoving();

	void animate();
	void render();

	void rotate(Vector newDirection);
	void keepOnMap();
};

#endif

