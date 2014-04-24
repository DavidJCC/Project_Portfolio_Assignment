#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "vector.h"
#include "LoadTextures.h"

/**
Simple class to represent a 'box' within the game universe.

It can be used to contain the 3D game objects which will rebound 
from the sides.

This class can be used with partitioning provided the domain 
fits entirely within the topmost partition. Prefereably
the domain should be slightly smaller than the largest
partition.
*/
class GameDomain
{
public:
	float lowX, highX;
	float lowY, highY;
	float lowZ, highZ;
	float r, g, b, a;
	Vector verts[8];

	GameDomain(void);
	GameDomain(float size);
	void setColor(float r, float g, float b, float a);
	void Render();
	void drawFace(int v0, int v1, int v2, int v3);
	void drawEdge(int v0, int v1);
	void calcCoordinates();
};
