#include "EnergyCoil.h"

EnergyCoil::EnergyCoil(float x, float y, float z) : MD2Model()
{
	m_pos.x = x; m_pos.y = y; m_pos.z = z;
	m_beenCollected = false;
	m_gluQuadric = gluNewQuadric();
	gluQuadricDrawStyle(m_gluQuadric, GLU_FILL);
	gluQuadricNormals(m_gluQuadric, GLU_NONE);
	r = 0.0f; g = 1.0f; b = 1.0f;
	m_bbRender = false;
	m_beenCollected = false;
	rotAngle = 10;
}

EnergyCoil::EnergyCoil(float x, float y, float z, char* modelFile, char* modelTex) : MD2Model()
{
	LoadMD2Model(modelFile, modelTex);
	m_pos.x = x; m_pos.y = y; m_pos.z = z;
	m_beenCollected = false;
	r = 0.0f; g = 0.0f; b = 1.0f;
	m_bbRender = false;
	m_beenCollected = false;
	rotAngle = 10;
}

EnergyCoil::~EnergyCoil(void)
{
	if(m_gluQuadric != NULL)
		gluDeleteQuadric(m_gluQuadric);
}

void EnergyCoil::render()
{
	glDisable(GL_LIGHTING);

	if(!m_beenCollected)
	{
		glColor3f(r, g, b);
		glPushMatrix();
		if(m_bbRender) bb.render();
			glTranslatef(m_pos.x, m_pos.y, m_pos.z);
			rotAngle+=2;
			glRotatef(rotAngle, 1,1,0);
			gluCylinder(m_gluQuadric, 10, 10, 7.0f, 100, 10);
		glPopMatrix();
	}

	glEnable(GL_LIGHTING);
}

void EnergyCoil::setRGB(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

bool EnergyCoil::collidesWith(MD2Model* model)
{
	if(this->bb.intersectAABBs(this->bb, this->getPos(), model->bb, model->getPos()))
		return true;
	else return false;
}

void EnergyCoil::move(float time)
{
	m_pos.x += m_vel.x * time;
	m_pos.y += m_vel.y * time;
	m_pos.z += m_vel.z * time;
}

void EnergyCoil::setVel(float x, float y, float z)
{
	m_vel.x = x;
	m_vel.y = y;
	m_vel.z = z;
}

void EnergyCoil::update(float time)
{
	move(time);
}

