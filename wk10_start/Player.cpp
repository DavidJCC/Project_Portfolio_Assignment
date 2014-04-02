#include "Player.h"

Player::Player(char* modelFile, char* modelTexture, int x, int y, int z) : MD2Model()
{
	score = 0;
	lives = 3;
	hasFlag = false;
	isMoving = false;
	LoadMD2Model(modelFile, modelTexture);
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

Player::~Player(void){
}

void Player::move(int x, int y, int z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
}

void Player::animate()	
{
	if(isMoving)
	{
		DisplayMD2Interpolate(30, 35, 0.1);
	}
	if(!isMoving)
	{
		DisplayMD2Interpolate(0, 39, 0.07);
	}
}

void Player::render()
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
		bb.render();
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	animate();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

std::string Player::getFlagStatus()
{
	if(this->hasFlag)
	{
		return "You have the flag";
	}
	else
	{
		return "You don't have the flag";
	}
}