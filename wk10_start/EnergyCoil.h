#ifndef __ENERGY_COIL_H
#define __ENERGY_COIL_H

#include "entity.h"
#include "random.h"

using namespace random;

class EnergyCoil : public Entity
{
private:
	float m_rotAngle;
	bool m_visibility;
	GLUquadricObj* m_gluQuadric; //used to represent the coil if a file isn't loaded
	int r, g, b, a;
	bool m_bbRender;
public:
	EnergyCoil(float x, float y, float z, char* modelfile, char* modelFile);
	~EnergyCoil(void);
	void render();
	void setVisibility(bool visibility) { m_visibility = visibility; }
	void bbRender(bool renderBB) { m_bbRender = renderBB; } //used to dis/enable the bounding box
	void setRGB(int r, int g, int b);	
	void removeCoil();
};

#endif

