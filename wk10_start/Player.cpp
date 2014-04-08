#include "Player.h"
#include "DebugPrint.h"

Player::Player(char* name, int x, int y, int z) : MD2Model()
{
	this->name = name;
	modelFile = "Data/pknight/pknight.md2";
	textureFile = "Data/pknight/pknight.bmp";
	LoadMD2Model(modelFile, textureFile);
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
	if(isSprinting)
	{
		pos.x += velocity.x * time * SPRINT_MULT;
		pos.y += velocity.y * time * SPRINT_MULT;
		pos.z += velocity.z * time * SPRINT_MULT;
	}
	else
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
		DisplayMD2Interpolate(RUN_START, RUN_END, ANIM_SPD);
	}
	else
	{
		firstTime = true;
		DisplayMD2Interpolate(IDLE_START, IDLE_END, ANIM_SPD);
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
		glRotatef(90.0f,-1,0,0);
	glPopMatrix();
	render();
}
