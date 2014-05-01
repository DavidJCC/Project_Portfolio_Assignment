#include "EnergyCoil.h"

EnergyCoil::EnergyCoil(float x, float y, float z, char* modelFile, char* modelTex) : Entity(x, y, z, modelFile, modelTex)
{
	m_pos.x = x; m_pos.y = y; m_pos.z = z;
	m_visibility = true;
	m_gluQuadric = gluNewQuadric();
	gluQuadricDrawStyle(m_gluQuadric, GLU_FILL);
	gluQuadricNormals(m_gluQuadric, GLU_NONE);
	r = 0.0f; g = 1.0f; b = 1.0f;
	m_bbRender = false;
	m_rotAngle = 10;
}

EnergyCoil::~EnergyCoil(void)
{
	if(m_gluQuadric != NULL)
		gluDeleteQuadric(m_gluQuadric);
}

void EnergyCoil::render()
{
	glDisable(GL_LIGHTING);

	if(m_visibility)
	{
		glColor3f(r, g, b);
		glPushMatrix();
		if(m_bbRender) bb.render();
			glTranslatef(m_pos.x, m_pos.y, m_pos.z);
			m_rotAngle+=1.0f;
			glRotatef(m_rotAngle, 0.0f, 1.0f, 0.0f);
			glScalef(0.5f, 0.5f, 0.5f);
			gluCylinder(m_gluQuadric, 10.0f, 10.0f, 7.0f, 100.0f, 10.0f);
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

void EnergyCoil::removeCoil()
{
	m_pos.y = -500;
}

