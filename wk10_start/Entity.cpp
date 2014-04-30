#include "Entity.h"

Entity::Entity(float x, float y, float z, char* modelFile, char* modelTex) : MD2Model()
{
	LoadMD2Model(modelFile, modelTex);
	m_pos.x = x;	m_pos.y = y;	m_pos.z = z;
	m_health = 100;
	m_lives = 3;
	m_bbRender = m_isMoving = m_isSprinting = m_isWalking = false;
	m_firstTime = true;
	m_rotAxis = m_dir = -1.0f, 0.0f, 0.0f;
	m_vel = Vector();
	m_angle = 90.0f;
}

Entity::Entity(float x, float y, float z)
{
	m_pos.x = x;	m_pos.y = y;	m_pos.z = z;
	m_health = 100;
	m_lives = 3;
	m_bbRender = m_isMoving = m_isSprinting = m_isWalking = false;
	m_firstTime = true;
	m_rotAxis = m_dir = -1.0f, 0.0f, 0.0f;
	m_vel = Vector();
	m_angle = 90.0f;
}

Entity::~Entity(void)
{
}

void Entity::setWalking(bool setWalking)
{
	m_isMoving = setWalking;
	m_isWalking = setWalking; 
		
}

void Entity::setSprinting(bool setSprinting) 
{
	if(m_isMoving)
	{
		m_isMoving = setSprinting;
		m_isSprinting = setSprinting; 
	}
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

void Entity::update(float time)
{
	move(time);
	keepOnMap();

	if(m_health < 1)
		setHealth(0);
}

void Entity::stopMoving()
{
	setVel(0, 0, 0);
	setWalking(false);
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
	}
	else
	{
		m_firstTime = true;
		DisplayMD2Interpolate(IDLE_START, IDLE_END, ANIM_SPD);
	}

	if(m_health == 0)
	{
		if(m_firstTime)
				this->myModel->interpol = 0.0;
			m_firstTime = false;
	}
}

void Entity::rotate()
{
	float rotAngle = 0;

	rotAngle = (m_vel).DotProduct(m_dir); 
	rotAngle = rotAngle * 180/float(M_PI);

	Vector rotAxis = (m_dir.UnitVector()).CrossProduct(m_vel.UnitVector()); 
	rotAxis.Normalize();
	
	render();
}

void Entity::render()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);		
		glRotatef(m_angle, m_rotAxis.x, m_rotAxis.y, m_rotAxis.z);
		if(m_bbRender) bb.render(); //render bounding box
		animate();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Entity::renderBB()
{
	if(m_bbRender)
		m_bbRender = false;
	else
		m_bbRender = true;
}

void Entity::keepOnMap()
{
}

bool Entity::collidesWith(Entity* entity)
{
	if(this->bb.intersectAABBs(this->bb, this->getPos(), entity->bb, entity->getPos()))
		return true;
	else return false;

}