#include "Skybox.h"


Skybox::Skybox(void)
{
}

Skybox::~Skybox(void)
{
}

void Skybox::init()
{
}

void Skybox::draw(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

	glDisable(GL_LIGHTING);
	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, texture[SKY_BACK]);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, texture[SKY_LEFT]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, texture[SKY_FRONT]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, texture[SKY_RIGHT]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Top side
	glBindTexture(GL_TEXTURE_2D, texture[SKY_TOP]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw bottom side
	glBindTexture(GL_TEXTURE_2D, texture[SKY_BOTTOM]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
	glEnd();
	//glEnable(GL_LIGHTING);
}

void Skybox::loadTextures()
{
	char s[60];

	for(int i = 0; i < 6; i++)
	{
		sprintf(s, "Images/Skybox/skybox%d.bmp", i);
		LoadTextures* lt = new LoadTextures(s);
		if(!lt) return;
		texture[i] = lt->getTexture();
		delete lt;
	}
}

void Skybox::kill()
{
	glDeleteTextures(6, texture);
}
