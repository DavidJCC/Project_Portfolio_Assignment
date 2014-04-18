#pragma once
#include "Entity.h"

class Zombie :	public Entity
{
public:
	Zombie(float x, float y, float z, char* modelFile, char* modelTex);
	~Zombie(void);

	void animate();
	void render();
};

