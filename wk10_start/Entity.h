#ifndef PLAYER_H
#define PLAYER_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "GameConstants.h"
#include "key_codes.h"
#include "MD2Model.h"

class Entity :	public MD2Model
{
protected:
	Vector m_velocity;
	Vector m_direction;
	int m_health;
	int m_lives;
	bool m_isMoving;
	bool m_firstTime;
	bool m_isWalking;
	bool m_isSprinting;
	bool m_bbRender;
	
public:
	Entity(int x, int y, int z, char* modelFile, char* modelTex);
	~Entity(void);

	//setters and getters
	int getLives() { return m_lives; }
	void setLives(int lives) { m_lives = lives; }

	void setHealth(int health) { m_health += health; }
	int getHealth() { return m_health; }

	void setWalking(bool setWalking);
	void setSprinting(bool setSprinting);

	void setBBRender(bool bbRender) { m_bbRender = bbRender; }
	bool getBBRender() { return m_bbRender; }
	void renderBB();

	void setPos(float x, float y, float z);
	void setVel(float x, float y, float z);
	void move(float time);
	void update(float time);
	void stopMoving();

	virtual	void animate() = 0; //pure virtual function
	virtual void render() = 0; //pure virtual function

	void rotate(Vector newDirection);
	void keepOnMap();
};

#endif

