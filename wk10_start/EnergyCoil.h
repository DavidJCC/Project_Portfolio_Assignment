#ifndef __ENERGY_COIL_H
#define __ENERGY_COIL_H

#include "vector.h"

class EnergyCoil
{
private:
	Vector m_pos;
public:
	EnergyCoil(float x, float y, float z, float size);
	~EnergyCoil(void);
};

#endif

