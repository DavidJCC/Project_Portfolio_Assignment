#include "Entity.h"
#include "DebugPrint.h"

Entity::Entity(int x, int y, int z, char* modelFile, char* modelTex) : MD2Model()
{
	LoadMD2Model(modelFile, modelTex);
	pos.x = x;	pos.y = y;	pos.z = z;
	m_rotAxis = m_direction = Vector();
	m_angle = 0.0f;
	m_health = 100;
	m_lives = 3;
	m_bbRender = m_isMoving = m_isSprinting = m_isWalking = false;
	m_firstTime = true;
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
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Entity::setVel(float x, float y, float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;
}

void Entity::move(float time)
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

void Entity::update(float time)
{
	move(time);
	keepOnMap();
}

void Entity::stopMoving()
{
	setVel(0, 0, 0);
	setWalking(false);
}

void Entity::rotate(Vector newDirection)
{
	float angle;
	Vector v1, v2;

	v1 = m_direction;
	v2 = newDirection;

	v1.Normalize();
	v2.Normalize();

	angle = v1.DotProduct(v2);
	setAngle(acos(angle)*180/M_PI); //convert to degrees

	setRotAxis( m_direction.CrossProduct(newDirection) );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glPushMatrix();	
		glRotatef(m_angle, m_rotAxis.x, m_rotAxis.y, m_rotAxis.z);
		render();
	glPopMatrix();
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