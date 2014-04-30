#ifndef __ENERGY_COIL_H
#define __ENERGY_COIL_H

#include "MD2Model.h"
#include "random.h"

using namespace random;

class EnergyCoil : public MD2Model
{
private:
	float rotAngle;
	Vector m_pos;
	Vector m_vel;
	bool m_beenCollected;
	GLUquadricObj* m_gluQuadric; //used to represent the coil if a file isn't loaded
	int r, g, b, a;
	bool m_bbRender;
public:
	EnergyCoil(float x, float y, float z, char* modelfile, char* modelFile);
	EnergyCoil(float x, float y, float z);
	~EnergyCoil(void);
	void render();
	void setCollected(bool collected) { m_beenCollected = collected; }
	void bbRender(bool renderBB) { m_bbRender = renderBB; } //used to dis/enable the bounding box
	void setRGB(int r, int g, int b);
	bool collidesWith(MD2Model* other);

	void move(float time);
	void setVel(float x, float y, float z);
	void setPos(float x, float y, float z);
	void update(float time);
};

#endif

