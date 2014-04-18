#include "Entity.h"
#include "DebugPrint.h"

Entity::Entity(int x, int y, int z) : MD2Model()
{
	m_pos = (x, y, z);
	m_vel = (0.0f, 0.0f, 0.0f);
	m_dir = (0.0f, 1.0f, 0.0f);
	m_health = 100;
	m_score = 0;
	m_lives = 3;
	m_bbRender = false;
	m_isMoving = m_isSprinting = m_isWalking = m_isJumping = false;
	m_firstTime = true;
}

Entity::~Entity(void)
{
}

void Entity::setPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Entity::setVel(float x, float y, float z)
{
	m_vel.x = x;
	m_vel.y = y;
	m_vel.z = z;
}

void Entity::update(float time)
{
	move(time);
}

void Entity::stopMoving()
{
	setVel(0, 0, 0);
}

void Entity::setWalking(bool setWalking)
{
	m_isMoving = setWalking;
	m_isWalking = setWalking; 
		
}

void Entity::setSprinting(bool setSprinting) 
{
	m_isMoving = setSprinting;
	m_isSprinting = setSprinting; 
}

void Entity::setJumping(bool isJumping)
{
	m_isMoving = isJumping;
	m_isJumping = isJumping;
}

void Entity::animate()
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
		if(m_isJumping)
		{
			if(m_firstTime)
				this->myModel->interpol = 0.0;
			m_firstTime = false;
			DisplayMD2Interpolate(JUMP_START, JUMP_END, ANIM_SPD);
		}
	}
	else
	{
		m_firstTime = true;
		DisplayMD2Interpolate(IDLE_START, IDLE_END, ANIM_SPD);
	}
}

void Entity::move(float time)
{
	if(m_isSprinting)
	{
		m_pos.x += m_vel.x * time * SPRINT_MULT;
		m_pos.y += m_vel.y * time * SPRINT_MULT;
		m_pos.z += m_vel.z * time * SPRINT_MULT;
	}
	else
		m_pos.x += m_vel.x * time;
		m_pos.y += m_vel.y * time;
		m_pos.z += m_vel.z * time;
}

void Entity::render()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		if(m_bbRender) bb.render(); //render bounding box
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		animate();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Entity::rotate(Vector newDirection)
{
	float rotAngle = acos((m_vel.UnitVector()).DotProduct(m_dir.UnitVector()));
	rotAngle = rotAngle * 180.0f/float(M_PI);

	Vector rotAxis = (m_dir.UnitVector()).CrossProduct(m_vel.UnitVector());
	rotAxis.Normalize();

	m_dir = rotAxis;

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		glRotatef(rotAngle, rotAxis.x, rotAxis.y, rotAxis.z);
	glPopMatrix();
}

void Entity::processKeyInput()
{

}
