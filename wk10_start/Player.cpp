#include "Player.h"
#include "DebugPrint.h"

Player::Player(char* name, int x, int y, int z) : MD2Model()
{
	m_name = name;
	m_modelFile = "Data/pknight/pknight.md2";
	m_textureFile = "Data/pknight/pknight.bmp";
	LoadMD2Model(m_modelFile, m_textureFile);
	m_direction = 0.0f, 0.0f, 1.0f;
	pos.x = x;
	pos.y = y;
	pos.z = z;
	m_health = 100;
	m_score = 0;
	m_lives = 3;
	m_hasFlag = m_bbRender = m_isMoving = m_isSprinting = m_isWalking = false;
	m_firstTime = true;
}

Player::~Player(void)
{
}

void Player::setWalking(bool setWalking)
{
	m_isMoving = setWalking;
	m_isWalking = setWalking; 
		
}

void Player::setSprinting(bool setSprinting) 
{
	if(m_isMoving)
	{
		m_isMoving = setSprinting;
		m_isSprinting = setSprinting; 
	}
}

void Player::setPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Player::setVel(float x, float y, float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;
}

void Player::move(float time)
{
	if(m_isSprinting)
	{
		pos.x += m_velocity.x * time * SPRINT_MULT;
		pos.y += m_velocity.y * time * SPRINT_MULT;
		pos.z += m_velocity.z * time * SPRINT_MULT;
	}
	else
		pos.x += m_velocity.x * time;
		pos.y += m_velocity.y * time;
		pos.z += m_velocity.z * time;
}

void Player::update(float time)
{
	move(time);
	keepOnMap();
}

void Player::stopMoving()
{
	setVel(0, 0, 0);
	setWalking(false);
}

void Player::animate()
{
	if(m_isMoving)
	{
		if(m_isWalking)
		{
			if(m_firstTime)
				this->myModel->interpol = 0.0;
			m_firstTime = false;
			DisplayMD2Interpolate(RUN_START, RUN_END, ANIM_SPD);
		}
		if(m_isSprinting)
		{
			if(m_firstTime)
				this->myModel->interpol = 0.0;
			m_firstTime = false;
			DisplayMD2Interpolate(RUN_START, RUN_END, ANIM_SPD);
		}
	}
	else
	{
		m_firstTime = true;
		DisplayMD2Interpolate(IDLE_START, IDLE_END, ANIM_SPD);
	}
}

void Player::render()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		if(m_bbRender) bb.render(); //render bounding box
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		animate();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Player::rotate(Vector newDirection)
{
	m_direction.Normalize();
	newDirection.Normalize();

	float angle = acos( m_direction.DotProduct( newDirection ) );
	angle = angle * 180/M_PI; //convert to degrees

	Vector rotAxis = m_direction.CrossProduct(newDirection);
	rotAxis.Normalize();

	//m_direction = rotAxis;

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);		
		glRotatef(angle, rotAxis.x, rotAxis.y, pos.z);
		render();
	glPopMatrix();
}

void Player::renderBB()
{
	if(getBBRender())
		setBBRender(false);
	else
		setBBRender(true);
}

void Player::keepOnMap()
{
}