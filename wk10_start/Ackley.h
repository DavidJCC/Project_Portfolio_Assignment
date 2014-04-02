#ifndef ACKLEY_H
#define ACKLEY_H

#include <math.h>

const double PI = atan(1.0) * 4.0;

class Ackley{
public:
	Ackley();
	double ack2Vars(double x, double y);
	void findMinMaxAckley(double sx, double sy, double ex, double ey, double step, double *max, double *min);
};

#endif