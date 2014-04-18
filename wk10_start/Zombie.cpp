#include "Zombie.h"


Zombie::Zombie(float x, float y, float z, char* modelFile, char* modelTex) : Entity(x, y, z, modelFile, modelTex)
{
	m_health = 50;
	m_lives = 1;
}


Zombie::~Zombie(void)
{
}

void Zombie::animate()
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

void Zombie::render()
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