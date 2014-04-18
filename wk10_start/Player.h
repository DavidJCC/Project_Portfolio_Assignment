#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player :	public Entity
{
private:
	bool m_hasFlag;
public:
	Player(float x, float y, float z);
	~Player(void);

	bool getFlagStatus() { return m_hasFlag; }
};

#endif