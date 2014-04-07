#pragma once
#include "LoadTextures.h"
		//load texture reference
		//0			1			2			3			4			5   
enum { SKY_LEFT=0, SKY_BACK, SKY_RIGHT, SKY_FRONT, SKY_TOP, SKY_BOTTOM };

class Skybox
{
private:
	unsigned int texture[6];	//the ids for the textures
	unsigned int imgNumbers[6];
public:
	Skybox(void);
	~Skybox(void);

	void init();
	void draw(float size); //void draw(float x, float y, float z, float width, float height, float length);
	void loadTextures();
	void kill();
};

