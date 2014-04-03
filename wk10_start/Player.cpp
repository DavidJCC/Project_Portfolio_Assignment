#include "Player.h"
#include "DebugPrint.h"

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
	firstTime = true;
	bbSwitch = false;
}

Player::~Player(void){
}

void Player::setPos(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
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

void Player::update(float time){
	move(time);
}

void Player::animate()
{
	if(isMoving)
	{
		if(firstTime)
			this->myModel->interpol = 0.0;
		firstTime = false;
		DisplayMD2Interpolate(RUN_START, RUN_END, 0.07f);
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
		//bb.render();
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