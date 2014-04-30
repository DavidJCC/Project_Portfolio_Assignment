#ifndef __PLAYER_H
#define __PLAYER_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "GameConstants.h"
#include "key_codes.h"
#include "MD2Model.h"
#include "DebugPrint.h"

class Entity :	public MD2Model
{
protected:
	Vector m_vel;
	Vector m_dir;
	Vector m_rotAxis;
	float m_angle;
	int m_health;
	int m_lives;
	bool m_isMoving;
	bool m_firstTime;
	bool m_isWalking;
	bool m_isSprinting;
	bool m_bbRender;
	
public:
	Entity(float x, float y, float z, char* modelFile, char* modelTex);
	Entity(float x, float y, float z);
	~Entity(void);

	//setters and getters
	int getLives() { return m_lives; }
	void setLives(int lives) { m_lives = lives; }

	void updateHealth(int health) { m_health += health; }
	void setHealth(int health) { m_health = health; }
	int getHealth() { return m_health; }

	void setWalking(bool setWalking);
	void setSprinting(bool setSprinting);

	void renderBB();

	void setPos(float x, float y, float z);
	void setVel(float x, float y, float z);
	void setRotAxis(Vector rotAxis) { m_rotAxis = rotAxis; }
	void setAngle(float angle) { m_angle = angle; }
	void setDir(Vector dir) { m_dir = dir; }

	void move(float time);
	void update(float time);
	void stopMoving();

	void animate();
	void render();

	void rotate();
	void keepOnMap();

	bool collidesWith(Entity* entity);
};

#endif

