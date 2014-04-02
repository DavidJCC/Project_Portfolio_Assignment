#pragma once
#include "LoadTextures.h"
#include "vector.h"
#include "GameConstants.h"

class Terrain
{
private: 
	Vector terrNorms[MAP_X * MAP_Z];
	unsigned int land;
public:
	float terrain[MAP_X * MAP_Z];

	Terrain(void);
	~Terrain(void);
	
	void init(char* terrBMP, char* terrTexture);
	void render();
	Vector calcAvgNormal(int x, int z);
	Vector normToPlane(Vector p1, Vector p2, Vector p3);
};

