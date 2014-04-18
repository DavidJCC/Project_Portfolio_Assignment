#ifndef ENTITY_H
#define ENTITY_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "GameConstants.h"
#include "MD2Model.h"

class Entity :	public MD2Model
{
private:
	int m_health;
	int m_score;
	int m_lives;
	bool m_bbRender;

	//animation
	bool m_isMoving;
	bool m_firstTime;
	bool m_isWalking;
	bool m_isSprinting;
	bool m_isJumping;	
public:
	Vector m_pos;
	Vector m_dir;
	Vector m_vel;

	Entity(int x, int y, int z);
	~Entity(void);

	int getScore() { return m_score; }
	void setScore(int score) { m_score = score; }

	int getLives() { return m_lives; }
	void setLives(int lives) { m_lives = lives; }

	void setHealth(int health) { m_health += health; }
	int getHealth() { return m_health; }

	void setBBRender(bool bbRender) { m_bbRender = bbRender; } //render the bounding box
	bool getBBRender() { return m_bbRender; }

	Vector getPos() { return m_pos; }
	void setPos(float x, float y, float z);
	Vector getVel() { return m_vel; }
	void setVel(float x, float y, float z);
	Vector getDir() { return m_dir; }
	void setDir(float x, float y, float z);

	void setWalking(bool setWalking);
	void setSprinting(bool setSprinting);
	void setJumping(bool setJumping);

	void move(float time);
	void update(float time);
	void stopMoving();

	void animate();
	void render();

	void rotate(Vector newDirection);
	void keepOnMap();

	void processKeyInput();
};

#endif

