#pragma once
#include "vector.h"

class Object{
public:
	virtual void render() = 0;
	virtual Vector& getPos() = 0;
};