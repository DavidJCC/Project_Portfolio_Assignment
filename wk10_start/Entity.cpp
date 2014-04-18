#include "Entity.h"
#include "DebugPrint.h"

Entity::Entity(int x, int y, int z, char* modelFile, char* modelTex) : MD2Model()
{
	LoadMD2Model(modelFile, modelTex);
	m_direction = 0.0f, 0.0f, 1.0f;
	pos.x = x;
	pos.y = y;
	pos.z = z;
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

void Entity::renderBB()
{
	if(getBBRender())
		setBBRender(false);
	else
		setBBRender(true);
}

void Entity::keepOnMap()
{
}