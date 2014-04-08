#include "Player.h"
#include "DebugPrint.h"

Player::Player(char* name, char* modelFile, char* modelTexture, int x, int y, int z) : MD2Model()
{
	this->name = name;
	LoadMD2Model(modelFile, modelTexture);
	pos.x = x;
	pos.y = y;
	pos.z = z;
	health = 100;
	score = 0;
	lives = 3;
	hasFlag = bbRender = isSprinting = isWalking = false;
	firstTime = true;
}

Player::~Player(void)
{
}

void Player::setPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Player::setVel(float x, float y, float z)
{
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

void Player::move(float time)
{
	pos.x += velocity.x * time;
	pos.y += velocity.y * time;
	pos.z += velocity.z * time;
}

void Player::update(float time)
{
	move(time);
}

void Player::stopMoving()
{
	setVel(0, 0, 0);
	setPlayerMoving(false);
}

void Player::walkAnimation()
{
	if(isWalking)
	{
		if(firstTime)
			this->myModel->interpol = 0.0;
		firstTime = false;
		DisplayMD2Interpolate(RUN_START, RUN_END, 0.09f);
	}
	else
	{
		firstTime = true;
		DisplayMD2Interpolate(0, 39, 0.01);
	}
}

void Player::render()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		if(bbRender) bb.render(); //render bounding box
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		walkAnimation();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Player::rotate()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
		glTranslatef(0, pos.y, 0);
		glRotatef(90.0f,0,1,0);
		render();
	glPopMatrix();
}
